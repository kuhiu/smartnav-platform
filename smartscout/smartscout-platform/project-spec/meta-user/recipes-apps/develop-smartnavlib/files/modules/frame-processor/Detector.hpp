#ifndef D968A4B7_3054_4F9B_90DE_9BE9B6BC4EA3
#define D968A4B7_3054_4F9B_90DE_9BE9B6BC4EA3

#include <memory>

#include "RecognitionResult.hpp"

#include "tensorflow/lite/interpreter.h"
#include "tensorflow/lite/kernels/register.h"
#include "tensorflow/lite/model.h"
#include "tensorflow/lite/optional_debug_tools.h"

#include <opencv2/opencv.hpp>

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
  std::vector<RecognitionResult> detect(const cv::Mat& image);

private:
  /** Model file name */
  static constexpr char const *__MODEL_FILE_NAME = {"/usr/bin/lite-model_efficientdet_lite0_detection_default_1.tflite"};
  /** Score threshold needed to be recognized  */
  const float __SCORE_THRESHOLD = 0.4;
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
  TfLiteStatus __fillInput(const cv::Mat& image);
  /** Neural network post processing */
  std::vector<RecognitionResult> __postProcess();
  /** Neural network pre processing */
  cv::Mat __preProcess(const cv::Mat& image);

};

#endif /* D968A4B7_3054_4F9B_90DE_9BE9B6BC4EA3 */
