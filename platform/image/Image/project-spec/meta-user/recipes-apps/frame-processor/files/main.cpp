#include "modules/Logger/Logger.hpp"
#include "modules/capture-frame/CaptureFrame.hpp"

void frameCaptureCallback(std::shared_ptr<FrameProcessor> frame_processor, void* data, unsigned int size) {
  auto __frame = std::make_shared<VirtualImage> (640, 480, 3, ColorSpaces::RGB, data);
  __frame->resize(320, 320);
  __frame->flip(false);
  __frame->colorBalancing(1.0);
  frame_processor->__processFrame(__frame);
  //rgb_image.saveAsJpg("testrgb.jpg");
}

int main () {
  
  Logger::log() << "Hello World Im frame processor";
  
	// Frame processor
	auto frame_processor = std::make_shared<FrameProcessor>();
  CaptureFrame capture_frame( frameCaptureCallback, 
                              640, 480, 
                              CaptureFrame::pixelFormat::PIX_FMT_RGB24,
                              frame_processor);

  while (true) {
    auto recognitions = frame_processor->getResults();
    std::cout << "Asking results... " << std::endl;
    for (auto &recognition : recognitions) {
      if (recognition.score > 0.3) {
        std::cout << "Results scores > 0.3 : " << recognition.score << std::endl;
      }
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  return 0;
}