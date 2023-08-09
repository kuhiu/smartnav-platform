#ifndef D768F8D4_85B1_4F5B_867B_9F2A7ADE2B52
#define D768F8D4_85B1_4F5B_867B_9F2A7ADE2B52

#include <opencv2/opencv.hpp>

#include <RecognitionResult.hpp>

namespace PixelMagic {
  /**
   * @brief Resize the image
   * 
   * @param image 
   * @param width 
   * @param height 
   * @return cv::Mat 
   */
  cv::Mat resize(const cv::Mat& image, uint32_t width, uint32_t height);
  /**
   * @brief Simple white balancing 
   * 
   * @param image 
   * @return cv::Mat 
   */
  cv::Mat simpleWhiteBalance(const cv::Mat& image);
  /**
   * @brief White balancing algorithm
	 * Reference: 
   * https://stackoverflow.com/questions/29166804/colorbalance-in-an-image-using-c-and-opencv
   * 
   * @param image 
   * @param percent 
   * @return cv::Mat 
   */
  cv::Mat colorBalancing(const cv::Mat& image, float percent);
	/**
	 * @brief Increase the saturation of the image 
	 * 
	 * @param value 
	 */
	cv::Mat increaseSaturation(const cv::Mat& image, int value);
	/**
	 * @brief Flip image 
	 * 
	 * @param image 
	 * @param orientation 0: vertically, 1: horizontal
	 * @return cv::Mat 
	 */
	cv::Mat flip(const cv::Mat& image, bool orientation);
	/**
	 * @brief Get the Brightness object
	 * 
	 * @return uint32_t 
	 */
	uint32_t getBrightness(const cv::Mat& image);
  /**
   * @brief Save the image as jpg format
   * 
   * @param image 
   * @param directory 
   */
  void saveAsJpg(const cv::Mat& image, const char* directory);
  /**
   * @brief Draw boundingBoxes into the image
   * 
   * @param image 
   * @param recognitions 
  */
  void drawBoundingBox(int img_width, int img_height, const cv::Mat& image, 
      std::vector<RecognitionResult> recognized_objects);
    
} // namespace PixelMagic

#endif /* D768F8D4_85B1_4F5B_867B_9F2A7ADE2B52 */
