#include "CaptureFrame.hpp"
#include "VirtualImage.hpp"
#include "ColorSpaces.hpp"

#include "modules/Logger/Logger.hpp"

void frameCallback(void* data, unsigned int size) {
  VirtualImage rgb_image(640, 480, 3, ColorSpaces::RGB, data);
  rgb_image.resize(320, 320);
  rgb_image.flip(false);
  rgb_image.colorBalancing(1.0);
  //rgb_image.saveAsJpg("testrgb.jpg");
}

int main() {
  Logger::log() << "Hello World Im testing CaptureFrame module";

  CaptureFrame capture_frame(frameCallback, 640, 480, CaptureFrame::pixelFormat::PIX_FMT_RGB24, 1);
  
  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  return 0;
}