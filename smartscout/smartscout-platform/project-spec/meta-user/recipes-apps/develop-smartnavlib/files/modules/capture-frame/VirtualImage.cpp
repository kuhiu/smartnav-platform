#include "VirtualImage.hpp"

VirtualImage::VirtualImage(uint32_t width, uint32_t height, uint32_t channels) 
		: __color_space(ColorSpaces::NONE) {
	switch (channels) {
	case 1:
		__data.create(height, width, CV_8UC1);
		break;
	case 3:
		__data.create(height, width, CV_8UC3);
		break;
	case 4:
		__data.create(height, width, CV_8UC4);
		break;
	default:
		throw(std::runtime_error("VirtualImage not support this channel size \n"));
		break;
	}
	__color_space = ColorSpaces::NONE;
}

VirtualImage::VirtualImage(uint32_t width, uint32_t height, uint32_t channels, ColorSpaces color_space, void *data) 
		: __color_space(color_space) {
	switch (channels) {
	case 1:
		__data = cv::Mat(height, width, CV_8UC1, data);
		break;
	case 3:
		__data = cv::Mat(height, width, CV_8UC3, data);
		break;
	case 4:
		__data = cv::Mat(height, width, CV_8UC4, data);
		break;
	default:
		throw(std::runtime_error("VirtualImage not support this channel size \n"));
		break;
	}
}

void VirtualImage::resize(uint32_t width, uint32_t height) {
  cv::resize(__data, __data, cv::Size(width, height), cv::INTER_AREA);
}

void VirtualImage::convertToRgb() {
	switch (__color_space) {
	case ColorSpaces(RGBA):
		cv::cvtColor(__data, __data, cv::COLOR_RGBA2RGB);
		__data.convertTo(__data, CV_8UC3);
		break;	
	default:
		throw(std::runtime_error("Colorspace not supported \n"));
		break;
	}
}

void VirtualImage::saveAsJpg(const std::string &directory) {
	cv::Mat bgr;

	switch (__color_space) {
	case ColorSpaces(RGB):
		cv::cvtColor(__data, bgr, cv::COLOR_RGB2BGR);
		cv::imwrite(directory.c_str(), bgr);
		break;
	case ColorSpaces(RGBA):
		cv::cvtColor(__data, bgr, cv::COLOR_RGBA2BGR);
		cv::imwrite(directory.c_str(), bgr);
		break;
	case ColorSpaces::BGR:
		cv::imwrite(directory.c_str(), __data);
		break;
	case ColorSpaces::BGRA:
		cv::imwrite(directory.c_str(), __data);
		break;
	default:
		throw(std::runtime_error("Colorspace not supported \n"));
		break;
	}
}

cv::Mat VirtualImage::getData() const { return __data; }

int VirtualImage::getWidth() const { 
	cv::Size size = __data.size();
	return (size.width);	 
}

int VirtualImage::getHeigth() const { 
	cv::Size size = __data.size();
	return (size.height);	 
};

int VirtualImage::getChannels() const { return __data.channels(); };

ColorSpaces VirtualImage::getColorSpace() const { return __color_space; };

// Reference: https://stackoverflow.com/questions/29166804/colorbalance-in-an-image-using-c-and-opencv
void VirtualImage::colorBalancing(float percent) {
	assert(__data.channels() == 3);
	assert(percent > 0 && percent < 100);

	float half_percent = percent / 200.0f;

	std::vector<cv::Mat> tmp_split; 
	split(__data, tmp_split);
	
	for(int i=0;i<3;i++) {
			//find the low and high precentile values (based on the input percentile)
			cv::Mat flat; 
			tmp_split[i].reshape(1,1).copyTo(flat);
			cv::sort(flat, flat, CV_SORT_EVERY_ROW + CV_SORT_ASCENDING);
			int lowval = flat.at<uchar>(cvFloor(((float)flat.cols) * half_percent));
			int highval = flat.at<uchar>(cvCeil(((float)flat.cols) * (1.0 - half_percent)));

			//saturate below the low percentile and above the high percentile
			tmp_split[i].setTo(lowval, tmp_split[i] < lowval);
			tmp_split[i].setTo(highval, tmp_split[i] > highval);

			//scale the channel
			normalize(tmp_split[i], tmp_split[i], 0, 255, cv::NORM_MINMAX);
	}
	merge(tmp_split,__data);
}

void VirtualImage::increaseSaturation(int value) {
	cv::Mat hsv;

	cv::cvtColor(__data, hsv, cv::COLOR_RGB2HSV);
	if (getColorSpace() == ColorSpaces::RGB) {
		for(int i = 0; i < hsv.rows; i++) {
			for(int j = 0; j < hsv.cols; j++) {
				// do something with HSV values...
				cv::Vec3b hsvPixel = hsv.at<cv::Vec3b>(i, j);
				hsvPixel[1] = hsvPixel[1] + value;
				if (hsvPixel[1] > 255) 
					hsvPixel[1] = 255;
			}
		}
		cv::cvtColor(hsv, __data, cv::COLOR_HSV2RGB);
	}
}

void VirtualImage::flip(bool orientation) {
	if (orientation)
		cv::flip(__data, __data, 1);
	else
		cv::flip(__data, __data, 0);
}

int VirtualImage::__getFootprint() {	
	cv::Size size = __data.size();
	return (size.width*size.height*__data.channels()); 
}