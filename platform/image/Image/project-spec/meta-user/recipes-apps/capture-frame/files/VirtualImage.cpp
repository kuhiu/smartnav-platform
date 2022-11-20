#include "VirtualImage.hpp"

VirtualImage::VirtualImage(uint32_t width, uint32_t height, uint32_t channels) : __width(width), __height(height), __channels(channels) {
	switch (channels) {
	case 1:
		__data.create(height, width, CV_8UC1);
		__type = CV_8UC1;
		__color_space = ColorSpaces(NONE);
		break;
	case 3:
		__data.create(height, width, CV_8UC3);
		__type = CV_8UC3;
		__color_space = ColorSpaces(NONE);
		break;
	case 4:
		__data.create(height, width, CV_8UC4);
		__type = CV_8UC4;
		__color_space = ColorSpaces(NONE);
		break;
	default:
		throw(std::runtime_error("VirtualImage not support this channel size \n"));
		break;
	}
}

VirtualImage::VirtualImage(uint32_t width, uint32_t height, uint32_t channels, ColorSpaces color_space, void *data) 
: __width(width), __height(height), __channels(channels), __color_space(color_space) {
	switch (channels) {
	case 1:
		__data = cv::Mat(height, width, CV_8UC1, data);
		__type = CV_8UC1;
		break;
	case 3:
		__data = cv::Mat(height, width, CV_8UC3, data);
		__type = CV_8UC3;
		break;
	case 4:
		__data = cv::Mat(height, width, CV_8UC4, data);
		__type = CV_8UC4;
		break;
	default:
		throw(std::runtime_error("VirtualImage not support this channel size \n"));
		break;
	}
}

void VirtualImage::resize(uint32_t width, uint32_t height) {
  cv::resize(__data, __data, cv::Size(width, height), cv::INTER_AREA);
  __width = width;
  __height = height;
}

void VirtualImage::rgbaToRgb() {
	if ( __color_space == ColorSpaces(RGBA)) {
		cv::cvtColor(__data, __data, cv::COLOR_RGBA2RGB);
		__data.convertTo(__data, CV_8UC3);
		__color_space = ColorSpaces(RGB);
		__type = CV_8UC3;
	}
	else 
		throw(std::runtime_error("rgbaToBgra failed! \n"));
}

void VirtualImage::saveAsJpg(const std::string &directory) {
	if ( __color_space == ColorSpaces(RGB) ) {
		cv::Mat bgr;
		cv::cvtColor(__data, bgr, cv::COLOR_RGB2BGR);
		cv::imwrite(directory.c_str(), bgr);
	}
	else if ( __color_space == ColorSpaces(RGBA) ) {
		cv::Mat bgr;
		cv::cvtColor(__data, bgr, cv::COLOR_RGBA2BGR);
		cv::imwrite(directory.c_str(), bgr);
	}
	else // bgr or bgra
		cv::imwrite(directory.c_str(), __data);
}

cv::Mat VirtualImage::getData() const { return __data; }

uint32_t VirtualImage::getWidth() const { return __width; }

uint32_t VirtualImage::getHeigth() const { return __height; };

uint32_t VirtualImage::getChannels() const { return __channels; };

ColorSpaces VirtualImage::getColorSpace() const { return __color_space; };

size_t VirtualImage::__getFootprint() {	return (__width*__height*__channels); }