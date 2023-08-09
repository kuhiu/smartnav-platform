#include "Detector.hpp"

#include <stdexcept>

//#define DEBUG_DETECTOR 1
#ifdef DEBUG_DETECTOR
 	#define DEBUG_PRINT(fmt, args...) printf( "DEBUG: %s:%d:%s(): " fmt, \
																						__FILE__, __LINE__, __func__, ##args)
#else
	#define DEBUG_PRINT(fmt, args...) /* Don't do anything in release builds */
#endif

Detector::Detector() {
  // Load model
  __model = tflite::FlatBufferModel::BuildFromFile(__MODEL_FILE_NAME);
  if (__model == nullptr)
    throw std::runtime_error("Model not initilizated \n");

  // Build the interpreter
  tflite::ops::builtin::BuiltinOpResolver resolver;
  tflite::InterpreterBuilder(*__model, resolver)(&__interpreter);
  if (!__interpreter)
    throw std::runtime_error("Interpreter not initilizated \n");

  // Allocate tensor buffers.
  if (__interpreter->AllocateTensors() != kTfLiteOk)
    throw std::runtime_error("Interpreter not initilizated \n");

  //DEBUG_PRINT("=== Pre-invoke Interpreter State ===\n");
  //tflite::PrintInterpreterState(__interpreter.get());

  DEBUG_PRINT("=== Number of input = %d, number of output = %d ===\n", __interpreter->inputs().size(), __interpreter->outputs().size());

  __input = std::unique_ptr<TfLiteTensor> (__interpreter->input_tensor(0));
  __output_detection_locations = std::unique_ptr<TfLiteTensor> (__interpreter->output_tensor(0));
  __output_detection_classes = std::unique_ptr<TfLiteTensor> (__interpreter->output_tensor(1));
  __output_detection_scores = std::unique_ptr<TfLiteTensor> (__interpreter->output_tensor(2));
  __output_num_detections = std::unique_ptr<TfLiteTensor> (__interpreter->output_tensor(3));

  DEBUG_PRINT("=== Input 0. bytes = %d, name %s, width %d  height %d channel %d ===\n", __input->bytes, __input->name,
      __input->dims->data[1], __input->dims->data[2], __input->dims->data[3]);
}

std::vector<RecognitionResult> Detector::detect(const cv::Mat& image) {
  // Pre process
  cv::Mat image_320x320 = __preProcess(image);
  // Fill input
  if (kTfLiteOk != __fillInput(image_320x320)) 
    throw(std::runtime_error("Image capture failed \n"));
  // Invoke 
  __interpreter->Invoke();
  // Post processing
  auto result = __postProcess();
  return result;
}

TfLiteStatus Detector::__fillInput(const cv::Mat& image) {  
  memcpy(__input->data.uint8, image.data, __input->bytes);
  return kTfLiteOk;
}

std::vector<RecognitionResult> Detector::__postProcess() {
  std::vector<RecognitionResult> recognitions;

  // Read CNN output
  float* detection_locations = __output_detection_locations->data.f;
  float* detection_classes = __output_detection_classes->data.f;
  float* detection_scores = __output_detection_scores->data.f;
  int num_detections = (int)*__output_num_detections->data.f;
  // If the recognition exceed the score threshold is saved 
  for (int i = 0; i < num_detections; ++i) {
    DEBUG_PRINT("detection_label %d, detection_score: %f\n", (int)detection_classes[i], detection_scores[i]);
    if (detection_scores[i] >= __SCORE_THRESHOLD) {
      RecognitionResult recognition_result;
      recognition_result.score = detection_scores[i];
      recognition_result.label = (int)detection_classes[i];
      recognition_result.ymin = detection_locations[i * 4];
      recognition_result.xmin = detection_locations[i * 4 + 1];
      recognition_result.ymax = detection_locations[i * 4 + 2];
      recognition_result.xmax = detection_locations[i * 4 + 3];
      recognitions.push_back(recognition_result);
    }
  }

  return recognitions;
}

cv::Mat Detector::__preProcess(const cv::Mat& image) {
  cv::Mat ret;

  if ((image.size().width != 320) || (image.size().height != 320)) 
    cv::resize(image, ret, cv::Size(320, 320), cv::INTER_AREA);
  else
    ret = image;
  return ret;
}