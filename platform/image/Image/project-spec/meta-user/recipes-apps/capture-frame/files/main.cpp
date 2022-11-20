#include "CaptureFrame.hpp"
#include "VirtualImage.hpp"
#include "ColorSpaces.hpp"

#include "modules/Logger/Logger.hpp"

void frameCallback(void* data, unsigned int size) {
  printf("Entre a frame callbac, size: %d\n", size);
  VirtualImage rgb_image(640, 480, 3, ColorSpaces::RGB, data);
  printf("Save as jpg\n");
  rgb_image.saveAsJpg("testrgb.jpg");
}

int main() {
  Logger::log() << "Hello World Im testing CaptureFrame module";

  CaptureFrame capture_frame(frameCallback, 640, 480, CaptureFrame::pixelFormat::PIX_FMT_RGB24, 4);
  
  printf("CaptureFrame was built\n");
  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }


  printf("Main: finish\n");
  return 0;
}