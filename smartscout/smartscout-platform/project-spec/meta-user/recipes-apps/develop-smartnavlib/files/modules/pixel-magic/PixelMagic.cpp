#include <PixelMagic.hpp>

#include <memory>

#include <opencv2/xphoto.hpp>

namespace PixelMagic {
  /**
   * @brief Resize the image
   * 
   * @param image 
   * @param width 
   * @param height 
   * @return cv::Mat 
   */
  cv::Mat resize(const cv::Mat& image, uint32_t width, uint32_t height) {
    cv::Mat ret;
    cv::resize(image, ret, cv::Size(width, height), cv::INTER_AREA);
    return ret;
  }
  /**
   * @brief Simple white balancing 
   * 
   * @param image 
   * @return cv::Mat 
   */
  cv::Mat simpleWhiteBalance(const cv::Mat& image) {
    cv::Ptr<cv::xphoto::SimpleWB> wb = cv::xphoto::createSimpleWB();
    cv::Mat ret;

    wb->balanceWhite(image, ret);
    return ret;
  }
  /**
   * @brief White balancing algorithm
	 * Reference: https://stackoverflow.com/questions/29166804/colorbalance-in-an-image-using-c-and-opencv
   * 
   * @param image 
   * @param percent 
   * @return cv::Mat 
   */
  cv::Mat colorBalancing(const cv::Mat& image, float percent) {
    cv::Mat ret;

    assert(image.channels() == 3);
    assert(percent > 0 && percent < 100);
    float half_percent = percent / 200.0f;
    std::vector<cv::Mat> tmp_split; 
    split(image, tmp_split);
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
    merge(tmp_split, ret);

    return ret;
  }
	/**
	 * @brief Increase the saturation of the image 
	 * 
	 * @param value 
	 */
	cv::Mat increaseSaturation(const cv::Mat& image, int value) {
    cv::Mat ret;
    cv::Mat hsv;

    assert(image.channels() == 3);
    cv::cvtColor(image, hsv, cv::COLOR_RGB2HSV);
    for(int i = 0; i < hsv.rows; i++) {
      for(int j = 0; j < hsv.cols; j++) {
        // do something with HSV values...
        cv::Vec3b hsvPixel = hsv.at<cv::Vec3b>(i, j);
        hsvPixel[1] = hsvPixel[1] + value;
        if (hsvPixel[1] > 255) 
          hsvPixel[1] = 255;
      }
    }
    cv::cvtColor(hsv, ret, cv::COLOR_HSV2RGB);
    return ret;
  }
	/**
	 * @brief Flip image 
	 * 
	 * @param image 
	 * @param orientation 0: vertically, 1: horizontal
	 * @return cv::Mat 
	 */
	cv::Mat flip(const cv::Mat& image, bool orientation) {
    cv::Mat ret;

  	if (orientation)
  		cv::flip(image, ret, 1);
  	else
  		cv::flip(image, ret, 0);
    return ret;
  }

	/**
	 * @brief Get the Brightness object
	 * 
	 * @return uint32_t 
	 */
	uint32_t getBrightness(const cv::Mat& image) {
		cv::Mat hsv;
		cv::Scalar mean;
		std::vector<cv::Mat> channels;

    assert(image.channels() == 3);
		cv::cvtColor(image, hsv, cv::COLOR_RGB2HSV);
		cv::split(hsv, channels);
		cv::Mat v_channel = channels[2];
		mean = cv::mean(v_channel);
		int ret = mean.val[0];
		return (((ret * 100) / 255));
	};
  /**
   * @brief Save the image as jpg format
   * 
   * @param image 
   * @param directory 
   */
  void saveAsJpg(const cv::Mat& image, const char* directory) {
    cv::imwrite(directory, image);
  };
    
} // namespace PixelMagic