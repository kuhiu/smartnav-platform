/* FIX IT: reference https://github.com/h4tr3d/v4l2-capture-complex/blob/master/main.cpp */

#include <fcntl.h>
#include <iostream>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>

#include <cstring>
#include <sstream>

#include <CaptureFrame.hpp>

//#define DEBUG_CAPTURE 1
#if defined(DEBUG_CAPTURE) 
 	#define DEBUG_PRINT(fmt, args...) printf( "DEBUG: %s:%d:%s(): " fmt, \
																						__FILE__, __LINE__, __func__, ##args)
#else
	#define DEBUG_PRINT(fmt, args...) /* Don't do anything in release builds */
#endif

CaptureFrame::CaptureFrame(EventCallback cb, uint32_t width, uint32_t height, pixelFormat pixel_format, uint32_t frame_count) 
	: __cb(cb), __frame_count(frame_count) {
	// Clear all v4l2 struct 
  CLEAR(__capability);
	CLEAR(__format);
	CLEAR(__parm);
	CLEAR(__req);

	__ov7670 = std::make_shared<ov7670>(width, height, ov7670::pixelFormat::SBGGR8_1X8, (uint32_t)5);
	__v_demosaic = std::make_shared<v_demosaic>(width, height, v_demosaic::pixelFormat::RBG888_1X24);

	__openDevice();
	__initDevice(width, height, pixel_format);
	
	__capture_frame_is_running = true;
	__capture_thread = std::thread(&CaptureFrame::__capture, this);
}

CaptureFrame::~CaptureFrame() {
	printf("Entre al destructor de capture frame\n");
	__capture_frame_is_running = false;
	__capture_thread.join();
	__uninitDevice();
	__closeDevice();
}

void CaptureFrame::__openDevice() {

	// Obtains info about the file pointed to by the device driver
	if (stat(__DEVICE, &__st) == -1) {
		std::ostringstream err;		
		err << "Cannot identify" << __DEVICE;
		std::cout << err.str() << std::endl;
		throw std::runtime_error(err.str());
	}

	// Check if the device driver is a char device
	if (!S_ISCHR(__st.st_mode)) {
		std::ostringstream err;
		err << __DEVICE << "isnt a char divice";
		std::cout << err.str() << std::endl;
		throw std::runtime_error(err.str());
	}

	// Open the device driver 
	__fd = open(__DEVICE, O_RDWR);
	if (__fd == -1) {
		std::ostringstream err;
		err << "Cannot open " << __DEVICE << "  Errno: " << strerror(errno);
		std::cout << err.str() << std::endl;
		throw std::runtime_error(err.str());
	}
}

void CaptureFrame::__closeDevice() {
	std::ostringstream err;

	if (close(__fd) == -1) {
		err << "Cannot close " << __DEVICE;
		std::cout << err.str() << std::endl;
		throw std::runtime_error(err.str());
	}
}

void CaptureFrame::__initDevice(uint32_t width, uint32_t height, pixelFormat pixelformat) {
	// Check if the driver is a V4L2 device
	if (__xioctl(__fd, VIDIOC_QUERYCAP, &__capability) == -1) {
		std::ostringstream err;
		if (EINVAL == errno) {
			err << __DEVICE << "is no V4L2 device. Errno: " << strerror(errno);
			std::cout << err.str() << std::endl;
			throw std::runtime_error(err.str());
		} else {
			err << "xioctl fail: VIDIOC_QUERYCAP. Errno: " << strerror(errno);
			std::cout << err.str() << std::endl;
			throw std::runtime_error(err.str());
		}
	}

	// Check if the driver is a capture device that supports multiplanar formats
	DEBUG_PRINT("capability.capabilities: %x\n", __capability.capabilities);
	if ( !(__capability.capabilities & V4L2_CAP_VIDEO_CAPTURE_MPLANE) ) {
		std::ostringstream err;
		err << __DEVICE << "is no video capture" <<
		"device that support multiplanar formats. Errno: " << strerror(errno);
		std::cout << err.str() << std::endl;
		throw std::runtime_error(err.str());
	}
	else {
		__driver_type = V4L2_CAP_VIDEO_CAPTURE_MPLANE;
		__buffer_type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	}

	// Set the frame rate
	__setFramerate();

	// Select video input, format and size
	__setFormat(width, height, pixelformat);

	// Init mmap
	__init_mmap();

	printf("Init device finished. \n");
}

void CaptureFrame::__uninitDevice() {
	for (int i = 0; i < __frame_count; ++i)
		for (int j = 0; j < __num_planes; j++)
			munmap(__image_buffers[i].start[j], __image_buffers[i].length[j]);
}

void CaptureFrame::__setFormat(uint32_t width, uint32_t height, pixelFormat pixelformat) {
	// Set format object
	__format.type = __buffer_type;

	switch (__driver_type) {
	case V4L2_CAP_VIDEO_CAPTURE_MPLANE:
		__setField(__format.fmt.pix_mp, width, height, pixelformat);
		break;
	default:
		throw std::runtime_error("Driver type unsupported.");
		break;
	}

	// Set format 
	if (__xioctl(__fd, VIDIOC_S_FMT, &__format) == -1) {
		std::ostringstream err;
		err << "VIDIOC_S_FMT. Errno: " << strerror(errno);
		std::cout << err.str() << std::endl;
		throw std::runtime_error(err.str());
	}

	// Print format
	//__getFormat();	
}

void CaptureFrame::__getFormat() {
	v4l2_format format {};
	format.type = __buffer_type;

	__xioctl(__fd, VIDIOC_G_FMT, &format);

	DEBUG_PRINT("Number of planes: %d\n", format.fmt.pix_mp.num_planes);
}

void CaptureFrame::__setFramerate() {
	int ret;
	__parm.type = __buffer_type;

	ret = __xioctl(__fd, VIDIOC_G_PARM, &__parm);
	if (ret < 0) {
		std::ostringstream err;
		err << "Unable to get frame rate";
		std::cout << err.str() << std::endl;
	}

	DEBUG_PRINT("Current Framerate %u/%u \n", 
			__parm.parm.capture.timeperframe.numerator, __parm.parm.capture.timeperframe.denominator);

	__parm.parm.capture.timeperframe.numerator = 1;
	__parm.parm.capture.timeperframe.denominator = 5;

	ret = __xioctl(__fd, VIDIOC_S_PARM, &__parm);
	if (ret < 0) {
		std::ostringstream err;
		err << "Unable to set frame rate. Errno: " << strerror(errno);
		std::cout << err.str() << std::endl;
	}

	ret = __xioctl(__fd, VIDIOC_G_PARM, &__parm);
	if (ret < 0) {
		std::ostringstream err;
		err << "Unable to get frame rate. Errno: " << strerror(errno);
		std::cout << err.str() << std::endl;
	}

	DEBUG_PRINT("New Framerate %u/%u \n", 
		__parm.parm.capture.timeperframe.numerator, __parm.parm.capture.timeperframe.denominator);
}

void CaptureFrame::__setField(v4l2_pix_format_mplane &field, uint32_t width, uint32_t height, pixelFormat pixel_format) {
	field.width       = width;
	field.height      = height;
	switch (pixel_format) {
	case PIX_FMT_RGB24:
		field.pixelformat = V4L2_PIX_FMT_RGB24;
		field.field       = V4L2_FIELD_NONE;
		field.num_planes  = __num_planes;
		for (int i = 0 ; i < __num_planes ; i++ ) {
			field.plane_fmt[i].bytesperline  = width * 3;
			field.plane_fmt[i].sizeimage  = width * height * 3;
		}
		break;
	default:
		throw std::runtime_error("Pixel format not supported\n");
		break;
	}
	field.field = V4L2_FIELD_NONE;
}

void CaptureFrame::__startCapturing() {
	unsigned int i;
	enum v4l2_buf_type type;

	for (i = 0; i < __frame_count; ++i) {
		v4l2_buffer buf;

		CLEAR(buf);
		buf.type = __buffer_type;
		buf.memory = V4L2_MEMORY_MMAP;
		buf.index = i;
		buf.m.planes = __image_buffers[i].planes;
		buf.length = __num_planes;
		
		DEBUG_PRINT("VIDIOC_QBUF buf index: %d\n", buf.index);
		if (__xioctl(__fd, VIDIOC_QBUF, &buf) == -1) {
			std::ostringstream err;
			err << "VIDIOC_QBUF: Fail. Errno: " << strerror(errno);
			std::cout << err.str() << std::endl;
			throw std::runtime_error(err.str());
		}
	}
	DEBUG_PRINT("Video stream on\n");
	CLEAR(type);
	type = V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE;
	int ret = __xioctl(__fd, VIDIOC_STREAMON, &type);
	while (ret == -1) {
		ret = __xioctl(__fd, VIDIOC_STREAMON, &type);
		DEBUG_PRINT("Waitting strem on.\n");
	}
	DEBUG_PRINT("Video stream on termino ioctl\n");
}

bool CaptureFrame::__readFrame(int frame_number) {
	v4l2_buffer buff;

	DEBUG_PRINT("Entre a read frame. \n");
	CLEAR(buff);
	buff.type = __buffer_type;
	buff.memory = V4L2_MEMORY_MMAP;
	buff.length = __num_planes;
	buff.m.planes = __image_buffers[buff.index].planes;
	if (__xioctl(__fd, VIDIOC_DQBUF, &buff) == -1) {
		std::ostringstream err;
		switch (errno) {
		case EAGAIN:
			return 0;
		default:
			err << "__readFrame. Errno: " << strerror(errno);
			std::cout << err.str() << std::endl;
			throw std::runtime_error(err.str());
		}
	}
	// Image ptr __image_buffers[buff.index].start[frame_number]
	// Image size buff.m.planes->bytesused
  auto rgb_image = std::make_shared<VirtualImage>(640, 480, 3, ColorSpaces::RGB, __image_buffers[buff.index].start[frame_number]);
  rgb_image->resize(320, 320);
  rgb_image->flip(false);
  rgb_image->colorBalancing(1.0);
	{ // Thread safe
		std::lock_guard<std::mutex> lock(__brightness_guard);
		__brightness = rgb_image->getBrightness();
	}
	// Callback
	__cb(rgb_image, this);
	// Deallocate image
	rgb_image = nullptr;
	return 1;
}

void CaptureFrame::__capture() {
	while(__capture_frame_is_running) {
		__startCapturing();

		for( int counter = 0; counter < __frame_count ; counter++) {
			fd_set fds;
			timeval tv;
			int ret;

			DEBUG_PRINT("Capturing counter: %d \n", counter);
			FD_ZERO(&fds);
			FD_SET(__fd, &fds);

			/* Timeout. */
			tv.tv_sec = 2;
			tv.tv_usec = 0;

			ret = select(__fd + 1, &fds, NULL, NULL, &tv);

			if (ret == -1) {
				throw std::runtime_error("select: FAIL");
			}

			if (!ret) {
				continue;
				//throw std::runtime_error("Select timeout!");
			}

			/* EAGAIN - continue select loop. */
			if (!__readFrame(counter))
				break;
		}
	}
}

int CaptureFrame::__xioctl(int fd, int request, void *arg) {
	int r;
	do {
		r = ioctl(fd, request, arg);
	} while (-1 == r && EINTR == errno);

	return r;
}

void CaptureFrame::__init_mmap() {
	__req.count = __frame_count;
	__req.type = __buffer_type;
	__req.memory = V4L2_MEMORY_MMAP;

	if (ioctl(__fd, VIDIOC_REQBUFS, &__req) == -1) {
		std::ostringstream err;
		if (EINVAL == errno) {
			err << __DEVICE << "Not support memory mapping! Errno: " << strerror(errno);
			std::cout << err.str() << std::endl;
			throw std::runtime_error(err.str());
		} else {
			err << __DEVICE << "VIDIOC_REQBUFS. Errno: " << strerror(errno);
			std::cout << err.str() << std::endl;
			throw std::runtime_error(err.str());
		}
	}

	if (__req.count < __frame_count) {
		std::ostringstream err;
		err << "Insufficient buffer memory on " << __DEVICE << "Errno: " << strerror(errno);
		std::cout << err.str() << std::endl;
		throw std::runtime_error(err.str());
	}

	// For each frame 
	for (int buffer_index = 0; buffer_index < __req.count; ++buffer_index) {
		v4l2_buffer buf;
		CLEAR(buf);
		ImageBuffer image_buffer;

		buf.type   = __buffer_type;
		buf.memory = V4L2_MEMORY_MMAP;
		buf.index  = buffer_index;
		buf.length = __num_planes;
		buf.m.planes = image_buffer.planes;

		DEBUG_PRINT("Buf index is %d\n", buf.index);
		if (__xioctl(__fd, VIDIOC_QUERYBUF, &buf) == -1) {
			std::ostringstream err;
			err << "VIDIOC_QUERYBUF. Errno: " << strerror(errno);
			std::cout << err.str() << std::endl;
			throw std::runtime_error(err.str());
		}

		// For each frame you wanna X number of planes
		for (size_t plane_index = 0; plane_index < buf.length; ++plane_index) { 
			image_buffer.start[plane_index] = 
					mmap(	nullptr, 
								buf.m.planes[plane_index].length, 
								PROT_READ|PROT_WRITE, MAP_SHARED, 
								__fd, 
								buf.m.planes[plane_index].m.mem_offset);
			if (MAP_FAILED == image_buffer.start[plane_index]) {
				std::ostringstream err;
				err << "Map fail. Errno: " << strerror(errno);
				std::cout << err.str() << std::endl;
				throw std::runtime_error(err.str());
			}
			image_buffer.length[plane_index] = buf.length;
		}
		__image_buffers.push_back(image_buffer);
	}
}