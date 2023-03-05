#include <v_demosaic.hpp>

#include <fcntl.h>
#include <iostream>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>

#include <cstring>
#include <memory>
#include <sstream>

//#define DEBUG_DEMOSAIC 1
#if defined(DEBUG_DEMOSAIC) 
 	#define DEBUG_PRINT(fmt, args...) printf( "DEBUG: %s:%d:%s(): " fmt, \
																						__FILE__, __LINE__, __func__, ##args)
#else
	#define DEBUG_PRINT(fmt, args...) /* Don't do anything in release builds */
#endif

v_demosaic::v_demosaic(uint32_t width, uint32_t height, pixelFormat pixel_format) {
	printf("v_demosaic constructor.\n");
	// Clear all v4l2 struct 
	CLEAR(__format);

	__openDevice();
	__initDevice(width, height, pixel_format);
}

v_demosaic::~v_demosaic() {
	printf("v_demosaic destructor.\n");
	__closeDevice();
}

void v_demosaic::__openDevice() {
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

void v_demosaic::__closeDevice() {
	std::ostringstream err;
	if (close(__fd) == -1) {
		err << "Cannot close " << __DEVICE;
		throw std::runtime_error(err.str());
	}
}

void v_demosaic::__initDevice(uint32_t width, uint32_t height, pixelFormat pixelformat) {
	// Set the frame rate
	//__setFramerate(frame_rate);
	// Select video input, format and size
	__setFormat(width, height, pixelformat);
	printf("Init device finished.\n");
}

void v_demosaic::__setFormat(uint32_t width, uint32_t height, pixelFormat pixelformat) {
	int ret;
	// Clear v4l2 struct 
	CLEAR(__format);
	// Set v4l2 struct
	__format.format.code = v4l2_mbus_pixelcode::V4L2_MBUS_FMT_SBGGR8_1X8;
	__format.format.width = width;
	__format.format.height = height;
	__format.format.field = v4l2_field::V4L2_FIELD_NONE;
	__format.pad = 0;
	__format.which = v4l2_subdev_format_whence::V4L2_SUBDEV_FORMAT_ACTIVE;
	ret = __xioctl(__fd, VIDIOC_SUBDEV_S_FMT, &__format);
	if (ret < 0) {
		std::ostringstream err;
		err << "Unable to get frame rate";
		throw std::runtime_error(err.str());
	}
	// Clear v4l2 struct 
	CLEAR(__format);
	ret = __xioctl(__fd, VIDIOC_SUBDEV_G_FMT, &__format);
	if (ret < 0) {
		std::ostringstream err;
		err << "Unable to get frame rate";
		throw std::runtime_error(err.str());
	}
	DEBUG_PRINT("Current Framerate %u/%u \n", 
			__format.format.width, __format.format.height);


	// Clear v4l2 struct 
	CLEAR(__format);
	ret = __xioctl(__fd, VIDIOC_SUBDEV_G_FMT, &__format);
	if (ret < 0) {
		std::ostringstream err;
		err << "Unable to get frame rate";
		throw std::runtime_error(err.str());
	}
	DEBUG_PRINT("Current Framerate %u %u \n", 
			__format.format.width, __format.format.height);
	// Clear v4l2 struct 
	CLEAR(__format);
	// Set v4l2 struct
	switch (pixelformat) {
	case RBG888_1X24:
		__format.format.code = v4l2_mbus_pixelcode::V4L2_MBUS_FMT_RGB888_1X24;
		break;
	default:
		throw std::runtime_error("pixelFormat unsupported.");
		break;
	}
	__format.format.width = width;
	__format.format.height = height;
	__format.pad = 1;
	__format.which = v4l2_subdev_format_whence::V4L2_SUBDEV_FORMAT_ACTIVE;
	ret = __xioctl(__fd, VIDIOC_SUBDEV_S_FMT, &__format);
	if (ret < 0) {
		std::ostringstream err;
		err << "Unable to get frame rate";
		throw std::runtime_error(err.str());
	}
	// Clear all v4l2 struct 
	CLEAR(__format);
	ret = __xioctl(__fd, VIDIOC_SUBDEV_G_FMT, &__format);
	if (ret < 0) {
		std::ostringstream err;
		err << "Unable to get frame rate";
		throw std::runtime_error(err.str());
	}
	DEBUG_PRINT("Current Framerate %u/%u \n", 
			__format.format.width, __format.format.height);
}