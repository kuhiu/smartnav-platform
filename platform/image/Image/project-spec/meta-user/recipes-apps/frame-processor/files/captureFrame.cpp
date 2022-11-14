#include "captureFrame.hpp"

captureFrame::captureFrame() {
  __physical_image = std::make_unique<PhyImage> (__width, __height, __channels, ColorSpaces(RGBA), (off_t)__FRAMEBUFFER_READ_OFFSET);
}

VirtualImage captureFrame::capture() {
  // Return a virtual image
  return (VirtualImage( __physical_image->getWidth(), 
                        __physical_image->getHeigth(), 
                        __physical_image->getChannels(), 
                        __physical_image->getColorSpace(), 
                        __physical_image->getData() ));
  
}