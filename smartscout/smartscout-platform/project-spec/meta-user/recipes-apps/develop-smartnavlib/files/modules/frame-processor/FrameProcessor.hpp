#ifndef __FRAMEPROCESSOR_H__
#define __FRAMEPROCESSOR_H__

#include <memory>
#include <mutex>

#include "Detector.hpp"

class FrameProcessor {
public:
  /**
   * @brief Get the Instance of the FrameProcessor
   * 
   * @return FrameProcessor& 
   */
  static FrameProcessor& getInstance();
  /**
   * @brief Deleting copy constructor
   * 
   * @param obj 
   */
  FrameProcessor(const FrameProcessor& obj) = delete;
  /**
   * @brief Singleton should not be assignable
   * 
   */
  void operator=(const FrameProcessor&) = delete;
  /**
   * @brief Consume the frame
   * 
   */
  void processFrame(const cv::Mat& frame);
  /**
   * @brief Get the Results object
   * 
   * @return std::vector<RecognitionResult> 
   */
  std::vector<RecognitionResult> getResults();
  /**
   * @brief Clear the results vector. The
   * memory is not deallocated. 
   * 
   */
  void clearResults() {
    __results.clear();
  };

private:
  /** Neural network detector */
  Detector __detector;
  /** Results */
  std::vector<RecognitionResult> __results;
  /** Result guard */
  std::mutex __result_guard;
  /** FrameProcessor constructor */
  FrameProcessor() = default;
  /** FrameProcessor destructor */
  ~FrameProcessor() = default;
  
};


#endif // __FRAMEPROCESSOR_H__