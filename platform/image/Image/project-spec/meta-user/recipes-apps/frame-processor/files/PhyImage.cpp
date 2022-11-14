#include "PhyImage.hpp"

#include <stdexcept>

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

PhyImage::PhyImage(uint32_t width, uint32_t height, uint32_t channels, ColorSpaces color_space, uint32_t phy_addr) 
									: __width(width), __height(height), __channels(channels), __color_space(color_space){
	__mem_fd = open("/dev/mem", O_RDWR | O_SYNC);
	if ( __mem_fd == -1) 
		throw(std::runtime_error("Open /dev/mem Failed \n"));
	
	// phys_addr should be page-aligned
	__data = mmap( NULL, 
      __getFootprint(), 
      PROT_READ | PROT_WRITE, 
      MAP_SHARED, 
      __mem_fd, 
      (off_t)phy_addr);		
	if(__data == MAP_FAILED)
		throw(std::runtime_error("Open /dev/mem Failed \n"));
}

PhyImage::~PhyImage() {
	munmap(__data, __getFootprint());
	close(__mem_fd);
}

void* PhyImage::getData() const { return __data; }

uint32_t PhyImage::getWidth() const { return __width; }

uint32_t PhyImage::getHeigth() const { return __height; };

uint32_t PhyImage::getChannels() const { return __channels; };

ColorSpaces PhyImage::getColorSpace() const { return __color_space; };

size_t PhyImage::__getFootprint() {	return (__width*__height*__channels); }