#ifndef __CAPTUREFRAME_H__
#define __CAPTUREFRAME_H__

#include <stdio.h>

#include "PhyImage.hpp"
#include "VirtualImage.hpp"

class captureFrame {
public:
  /** captureFrame constructor */
  captureFrame();
  /** captureFrame destructor */
  ~captureFrame() = default;
  /**
   * @brief Capture one frame from RAM.
   * 
   * @return PhyImage 
   */
  VirtualImage capture();

private:
  /** Image widht */
  const uint32_t __width = 320;
  /** Image height */
  const uint32_t __height = 240;
  /** Image channels */
  const uint32_t __channels = 4;
  /** Ram offset where image is located */
  const off_t __FRAMEBUFFER_READ_OFFSET = 0x01000000;
  /** Physical image */
  std::unique_ptr<PhyImage> __physical_image;
};



#endif // __CAPTUREFRAME_H__