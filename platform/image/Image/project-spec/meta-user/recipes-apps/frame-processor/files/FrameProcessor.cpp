#include "FrameProcessor.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

FrameProcessor::FrameProcessor() {
  __is_running = true;

  printf("Open vdma driver\n");
  if ( (__vdma_fd = open("/dev/vdma_control_chardev", O_RDWR)) == -1)
    throw std::runtime_error("Could not open vdma driver\n");

  __processor_thread = std::thread(&FrameProcessor::__processFrame, this);
}

FrameProcessor::~FrameProcessor() {
  __is_running = false;
  __processor_thread.join();
}

void FrameProcessor::saveFrame(const VirtualImage &frame) {
  std::unique_lock<std::mutex> frame_lock(__frame_guard);
  if (__frame == nullptr) {
    // Create a virtual image
    __frame = std::make_shared<VirtualImage>(frame); 
    // Manual unlocking is done before notifying, to avoid waking up
    // the waiting thread only to block again (see notify_one for details)
    frame_lock.unlock();
    __cv.notify_one();
  }
}

std::vector<RecognitionResult> FrameProcessor::getResults() { 
  std::unique_lock<std::mutex> lock(__result_guard);
  return __results; 
}

void FrameProcessor::__processFrame() {
  while(__is_running) {
    std::unique_lock<std::mutex> frame_lock(__frame_guard);
    __cv.wait(frame_lock, [&] () {
      return (__frame != nullptr);
    });
    __consumeFrame();
    __frame = nullptr;
  }
}

void FrameProcessor::__consumeFrame() {
  // Start measuring time
  auto begin = std::chrono::high_resolution_clock::now();
  __frame->saveAsJpg("test2.jpg");

  { // Run Person detector 
    std::unique_lock<std::mutex> lock(__result_guard);
    __results = __detector.detect(__frame);
  }

  // Stop measuring time and calculate the elapsed time
  auto end = std::chrono::high_resolution_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

  std::cout << "Time recognition" << (elapsed.count() * 1e-9) << "seconds" << std::endl;
}