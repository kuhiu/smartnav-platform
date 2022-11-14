#ifndef __FRAMEPROCESSOR_H__
#define __FRAMEPROCESSOR_H__

#include <condition_variable>
#include <memory>
#include <mutex>
#include <thread>

#include "Detector.hpp"
#include "PhyImage.hpp"

class FrameProcessor {
public:
  /** FrameProcessor constructor */
  FrameProcessor();
  /** FrameProcessor destructor */
  ~FrameProcessor();
  /**
   * @brief Save frame
   * 
   * @param frame 
   */
  void saveFrame(const VirtualImage &frame);
  /**
   * @brief Get the Results object
   * 
   * @return std::shared_ptr<std::vector<RecognitionResult>> 
   */
  std::vector<RecognitionResult> getResults();

private:
  /** Vdma file descriptor */
  int __vdma_fd;
  /** Thread state */
  bool __is_running;
  /** Neural network detector */
  Detector __detector;
  /** Image frame */
  std::shared_ptr<VirtualImage> __frame;
  /** Frame guard */
  std::mutex __frame_guard;
  /** Condition variable */
  std::condition_variable __cv;
  /** Processor thread */
  std::thread __processor_thread;
  /** Result guard */
  std::mutex __result_guard;
  /** Results */
  std::vector<RecognitionResult> __results;
  /**
   * @brief Process the frame 
   * 
   */
  void __processFrame();
  /**
   * @brief Consume the frame
   * 
   */
  void __consumeFrame();
};


#endif // __FRAMEPROCESSOR_H__