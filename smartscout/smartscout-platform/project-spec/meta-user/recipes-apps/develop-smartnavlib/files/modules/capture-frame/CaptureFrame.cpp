#include <CaptureFrame.hpp>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

CaptureFrame *CaptureFrame::__instance = nullptr;

CaptureFrame *CaptureFrame::getInstance(uint32_t width, uint32_t height) {
  if (__instance == nullptr) {
    __instance = new CaptureFrame(width, height);
  }
  return __instance;
}

CaptureFrame::CaptureFrame(uint32_t width, uint32_t height) 
  : __IMG_WIDTH(width), __IMG_HEIGHT(height) {
  __memFd = open("/dev/mem", O_RDWR | O_SYNC);
  if (__memFd == -1) {
      std::ostringstream err;
      err << "Could not open /dev/mem ";
      throw std::runtime_error(err.str());
  }
  __readBuffer = mmap(NULL, __IMG_WIDTH*__IMG_HEIGHT*__IMG_CHANNELS, PROT_READ | PROT_WRITE, MAP_SHARED, __memFd, __READ_OFFSET);		
  if(__readBuffer == MAP_FAILED){
      std::ostringstream err;
      err << "Mapping read buffer Failed ";
      throw std::runtime_error(err.str());
  }
  __writeBuffer = mmap(NULL, __IMG_WIDTH*__IMG_HEIGHT*__IMG_CHANNELS, PROT_READ | PROT_WRITE, MAP_SHARED, __memFd, __WRITE_OFFSET );	
  if(__writeBuffer == MAP_FAILED){
      std::ostringstream err;
      err << "Mapping write buffer Failed ";
      throw std::runtime_error(err.str());
  }
  __image.create(__IMG_HEIGHT, __IMG_WIDTH, CV_8UC4);
};

CaptureFrame::~CaptureFrame() {
  munmap(__readBuffer, __IMG_WIDTH*__IMG_HEIGHT*__IMG_CHANNELS);
  munmap(__writeBuffer, __IMG_WIDTH*__IMG_HEIGHT*__IMG_CHANNELS);
  close(__memFd);
}; 

const cv::Mat& CaptureFrame::getFrame() {
  // Read mem address 
  memcpy(__image.data, __readBuffer, __IMG_WIDTH*__IMG_HEIGHT*__IMG_CHANNELS);
  // Add support for openCV
  cv::cvtColor(__image, __img_bgr, cv::COLOR_RGBA2BGR);
  return __img_bgr;
}
