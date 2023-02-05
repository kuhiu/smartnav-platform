#ifndef __FRAMEPROCESSOR_H__
#define __FRAMEPROCESSOR_H__

#include <memory>
#include <mutex>

#include "Detector.hpp"

class FrameProcessor {
public:
  /** FrameProcessor constructor */
  FrameProcessor() = default;
  /** FrameProcessor destructor */
  ~FrameProcessor() = default;
  /**
   * @brief Consume the frame
   * 
   */
  void processFrame(std::shared_ptr<VirtualImage> frame);
  /**
   * @brief Get the Results object
   * 
   * @return std::vector<RecognitionResult> 
   */
  std::vector<RecognitionResult> getResults();

private:
  /** Neural network detector */
  Detector __detector;
  /** Results */
  std::vector<RecognitionResult> __results;
  /** Result guard */
  std::mutex __result_guard;

};


#endif // __FRAMEPROCESSOR_H__