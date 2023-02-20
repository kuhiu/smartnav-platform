#include <ov7670.hpp>

#include <fcntl.h>
#include <iostream>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>

#include <cstring>
#include <memory>
#include <sstream>

#define DEBUG_OV7670
#ifdef DEBUG_OV7670
 	#define DEBUG_PRINT(fmt, args...) printf( "DEBUG: %s:%d:%s(): " fmt, \
																						__FILE__, __LINE__, __func__, ##args)
#else
	#define DEBUG_PRINT(fmt, args...) /* Don't do anything in release builds */
#endif

ov7670::ov7670(uint32_t width, uint32_t height, pixelFormat pixel_format, uint32_t frame_rate) {
	printf("ov7670 constructor.\n");
	// Clear all v4l2 struct 
	CLEAR(__format);
	CLEAR(__frame_interval);
	__openDevice();
	__initDevice(width, height, pixel_format, frame_rate);
}

ov7670::~ov7670() {
	printf("ov7670 destructor.\n");
	__closeDevice();
}

void ov7670::__openDevice() {
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

void ov7670::__closeDevice() {
	std::ostringstream err;
	if (close(__fd) == -1) {
		err << "Cannot close " << __DEVICE;
		throw std::runtime_error(err.str());
	}
}

void ov7670::__initDevice(uint32_t width, uint32_t height, pixelFormat pixelformat, uint32_t frame_rate) {
	// Select video input, format and size
	__setFormat(width, height, pixelformat);
	// Set the frame rate
	__setFramerate(frame_rate);
	printf("Init device finished.\n");
}

void ov7670::__setFormat(uint32_t width, uint32_t height, pixelFormat pixelformat) {
	int ret;

	ret = __xioctl(__fd, VIDIOC_SUBDEV_G_FMT, &__format);
	if (ret < 0) {
		std::ostringstream err;
		err << "Unable to get frame rate";
		throw std::runtime_error(err.str());
	}
	DEBUG_PRINT("Current format %u/%u \n", 
			__format.format.width, __format.format.height);
	switch (pixelformat) {
	case SBGGR8_1X8:
		__format.format.code = v4l2_mbus_pixelcode::V4L2_MBUS_FMT_SBGGR8_1X8;
		break;
	default:
		throw std::runtime_error("pixelFormat unsupported.");
		break;
	}
	__format.format.width = width;
	__format.format.height = height;
	__format.which = v4l2_subdev_format_whence::V4L2_SUBDEV_FORMAT_ACTIVE;
	ret = __xioctl(__fd, VIDIOC_SUBDEV_S_FMT, &__format);
	if (ret < 0) {
		std::ostringstream err;
		err << "Unable to get frame rate";
		throw std::runtime_error(err.str());
	}
	ret = __xioctl(__fd, VIDIOC_SUBDEV_G_FMT, &__format);
	if (ret < 0) {
		std::ostringstream err;
		err << "Unable to get frame rate";
		throw std::runtime_error(err.str());
	}
	DEBUG_PRINT("Current format %u/%u \n", 
			__format.format.width, __format.format.height);
}

void ov7670::__setFramerate(uint32_t frame_rate) {
	int ret;

	__frame_interval.interval.numerator = 1;
	__frame_interval.interval.denominator = frame_rate;

	ret = __xioctl(__fd, VIDIOC_SUBDEV_S_FRAME_INTERVAL, &__frame_interval);
	if (ret < 0) {
		std::ostringstream err;
		err << "Unable to set frame rate";
		throw std::runtime_error(err.str());
	}
}

