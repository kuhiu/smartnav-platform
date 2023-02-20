#include "FrameProcessor.hpp"

#include <chrono>
#include <mutex>

void FrameProcessor::processFrame(std::shared_ptr<VirtualImage> frame) {
  // Start measuring time
  auto begin = std::chrono::high_resolution_clock::now();

  { // Run Person detector 
    std::unique_lock<std::mutex> lock(__result_guard);
    __results = __detector.detect(frame);
  }

  // Stop measuring time and calculate the elapsed time
  auto end = std::chrono::high_resolution_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

  std::cout << "Time recognition " << (elapsed.count()/1000) << " seconds" << std::endl;
}

std::vector<RecognitionResult> FrameProcessor::getResults() { 
  std::unique_lock<std::mutex> lock(__result_guard);
  return __results;
}