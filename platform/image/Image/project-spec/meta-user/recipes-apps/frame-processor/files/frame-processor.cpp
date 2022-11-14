#include "captureFrame.hpp"
#include "FrameProcessor.hpp"

int main () {
  // Frame processor
  FrameProcessor frame_processor;
  // Capture frame 
  captureFrame capture_frame;

  while(1) {
    // Capture image
    VirtualImage virtual_image = capture_frame.capture();
    virtual_image.saveAsJpg("test1.jpg");

    // Save frame 
    frame_processor.saveFrame(virtual_image);

    auto results = frame_processor.getResults();

    std::cout << "Asking results... " << std::endl;
    for (auto &result : results) {
      if (result.score > 0.3) {
        std::cout << "Results scores > 0.3 : " << result.score << std::endl;
      }
    }
  }

  return 0;
}