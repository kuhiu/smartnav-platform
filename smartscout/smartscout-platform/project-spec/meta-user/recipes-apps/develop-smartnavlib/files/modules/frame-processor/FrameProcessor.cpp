#include "FrameProcessor.hpp"

#include <chrono>
#include <mutex>

FrameProcessor& FrameProcessor::getInstance() {
  static FrameProcessor instance; 
  return instance;
}

void FrameProcessor::processFrame(const cv::Mat& frame) {
  // Start measuring time
  auto begin = std::chrono::high_resolution_clock::now();

  { // Run detector 
    std::lock_guard<std::mutex> lock(__result_guard);
    __results = __detector.detect(frame);
  }

  // Stop measuring time and calculate the elapsed time
  auto end = std::chrono::high_resolution_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

  // std::cout << "Time recognition " << (elapsed.count()/1000) << " seconds" << std::endl;
}

std::vector<RecognitionResult> FrameProcessor::getResults() { 
  std::lock_guard<std::mutex> lock(__result_guard);
  return __results;
}