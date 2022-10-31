#ifndef __PHYIMAGE_H__
#define __PHYIMAGE_H__

#include <stdint.h>

#include <memory>

class PhyImage {
public:
  /** PhyImage constructor */
  PhyImage(uint32_t width, uint32_t height, uint32_t channels, uint32_t phy_addr);
  /** PhyImage desconstructor */
  ~PhyImage();
  /**
	 * @brief Get the Data 
	 * 
	 * @return cv::Mat 
	 */
	void* getData() const;
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

private:
	/** Memory file descriptor */
	int __mem_fd;
	/** Image data */
	void *__data;
	/** Image width */
	const uint32_t __width;
	/** Image height */
	const uint32_t __height;
	/** Image channels*/
	const uint32_t __channels;
	/**
	 * @brief Get image footprint
	 * 
	 * @return size_t 
	 */
	size_t __getFootprint();

};



#endif // __PHYIMAGE_H__