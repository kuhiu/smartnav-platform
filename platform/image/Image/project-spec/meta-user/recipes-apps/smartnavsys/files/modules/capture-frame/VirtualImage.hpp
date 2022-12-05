#ifndef __VIRTUALIMAGE_H__
#define __VIRTUALIMAGE_H__

#include <stdint.h>
#include <memory>

#include <opencv2/opencv.hpp>

#include "ColorSpaces.hpp"

class VirtualImage {
public:
  /** VirtualImage constructor */
	VirtualImage(uint32_t width, uint32_t height, uint32_t channels);
  /** VirtualImage constructor */
	VirtualImage(uint32_t width, uint32_t height, uint32_t channels, ColorSpaces color_space, void *data);
  /** VirtualImage destructor */
  ~VirtualImage() = default;
  /**
   * @brief Resize image
   * 
   * @param width 
   * @param height 
   * @return * Resize 
   */
  void resize(uint32_t width, uint32_t height);
	/**
	 * @brief convert the input format to rgb
	 * 
	 */
	void convertToRgb();
	/**
	 * @brief Save image as jpeg
	 * 
	 * @param directory 
	 */
	void saveAsJpg(const std::string &directory);
	/**
	 * @brief Get the Data 
	 * 
	 * @return cv::Mat 
	 */
	cv::Mat getData() const;
	/**
	 * @brief Get the Width object
	 * 
	 * @return int 
	 */
	int getWidth() const;
	/**
	 * @brief Get the Heigth object
	 * 
	 * @return int 
	 */
	int getHeigth() const;
	/**
	 * @brief Get the Channels object
	 * 
	 * @return int 
	 */
	int getChannels() const;
	/**
	 * @brief Get the Color Space object
	 * 
	 * @return colorSpace 
	 */
	ColorSpaces getColorSpace() const;
	/**
	 * @brief Color balancing algorithm
	 * 
	 * @param percent 
	 */
	void colorBalancing(float percent);
	/**
	 * @brief Flip image 
	 * 
	 * @param orientation 0: vertically, 1: horizontal
	 */
	void flip(bool orientation);

private:
  /** Image data */
	cv::Mat __data;
	/** Image colorspace */
	ColorSpaces __color_space;
	/**
	 * @brief Get image footprint
	 * 
	 * @return int 
	 */
	int __getFootprint();

};



#endif // __VIRTUALIMAGE_H__