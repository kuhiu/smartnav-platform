#ifndef __DETECTOR_H__
#define __DETECTOR_H__

#include <memory>

#include "RecognitionResult.hpp"
#include "modules/capture-frame/VirtualImage.hpp"

#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/model.h"
#include "tensorflow/lite/optional_debug_tools.h"

class Detector {
public:
  /** Detector constructor */
  Detector();
  /** Detector destructor */
  ~Detector() = default;
  /**
   * @brief Process a new frame 
   * 
   * @param image 
   */
  std::vector<RecognitionResult> detect(std::shared_ptr<VirtualImage> image);

private:
  /** Model file name */
  static constexpr char const *__MODEL_FILE_NAME = {"lite-model_ssd_mobilenet_v2_100_int8_default_1.tflite"};
  /** Score threshold needed to be recognized  */
  const float __SCORE_THRESHOLD = 0.5;
	/** Tflite model */
	std::unique_ptr<tflite::FlatBufferModel> __model;
	/** Tflite interpreter */
	std::unique_ptr<tflite::Interpreter> __interpreter;
	/** Tflite i/o */
	std::unique_ptr<TfLiteTensor> __input;
  std::unique_ptr<TfLiteTensor> __output_detection_locations;
  std::unique_ptr<TfLiteTensor> __output_detection_classes;
  std::unique_ptr<TfLiteTensor> __output_detection_scores;
  std::unique_ptr<TfLiteTensor> __output_num_detections;
  /** Fill tensorflow input */
  TfLiteStatus __fillInput(uint32_t image_width, uint32_t image_height, uint32_t channels, std::shared_ptr<VirtualImage> image);
  /** Neural network post processing */
  std::vector<RecognitionResult> __postProcess(std::shared_ptr<VirtualImage> image);
  /** Neural network pre processing */
  void __preProcess(std::shared_ptr<VirtualImage> image);

};

#endif // __DETECTOR_H__