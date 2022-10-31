#ifndef __VIRTUALIMAGE_H__
#define __VIRTUALIMAGE_H__

#include <cinttypes>
#include <memory>

#include <opencv2/opencv.hpp>

enum colorSpace {
	NONE = 0,
	RGB,
	RGBA,
	BGR,
	BGRA,

};

class VirtualImage {
public:
  /** VirtualImage constructor */
	VirtualImage(uint32_t width, uint32_t height, uint32_t channels);
  /** VirtualImage constructor */
	VirtualImage(uint32_t width, uint32_t height, uint32_t channels, colorSpace color_space, void *data);
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
	 * @brief RGBA to RGB
	 * 
	 */
	void rgbaToRgb();
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
	 * @return uint32_t 
	 */
	uint32_t getWidth() const;
	/**
	 * @brief Get the Heigth object
	 * 
	 * @return uint32_t 
	 */
	uint32_t getHeigth() const;
	/**
	 * @brief Get the Channels object
	 * 
	 * @return uint32_t 
	 */
	uint32_t getChannels() const;
	/**
	 * @brief Get the Color Space object
	 * 
	 * @return colorSpace 
	 */
	colorSpace getColorSpace() const;

private:
  /** Image data */
	cv::Mat __data;
	/** Image width */
	uint32_t __width;
	/** Image height */
	uint32_t __height;
	/** Image channels*/
	const uint32_t __channels;
	/** Image type */
	int __type;
	/** Image color space */
	colorSpace __color_space;
	/**
	 * @brief Get image footprint
	 * 
	 * @return size_t 
	 */
	size_t __getFootprint();

};



#endif // __VIRTUALIMAGE_H__