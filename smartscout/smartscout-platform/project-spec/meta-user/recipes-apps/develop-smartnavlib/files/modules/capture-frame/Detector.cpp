#include "Detector.hpp"

#include <stdexcept>

//#define DEBUG_DETECTOR 1
#ifdef DEBUG_DETECTOR
#define DEBUG_PRINT(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...) do {} while (0)
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

  DEBUG_PRINT("=== Pre-invoke Interpreter State ===\n");
  tflite::PrintInterpreterState(__interpreter.get());

  DEBUG_PRINT("=== Number of input = %d, number of output = %d ===\n", __interpreter->inputs().size(), __interpreter->outputs().size());

  __input = std::unique_ptr<TfLiteTensor> (__interpreter->input_tensor(0));
  __output_detection_locations = std::unique_ptr<TfLiteTensor> (__interpreter->output_tensor(0));
  __output_detection_classes = std::unique_ptr<TfLiteTensor> (__interpreter->output_tensor(1));
  __output_detection_scores = std::unique_ptr<TfLiteTensor> (__interpreter->output_tensor(2));
  __output_num_detections = std::unique_ptr<TfLiteTensor> (__interpreter->output_tensor(3));

  DEBUG_PRINT("=== Input 0. bytes = %d, name %s, width %d  height %d channel %d ===\n", __input->bytes, __input->name,
      __input->dims->data[1], __input->dims->data[2], __input->dims->data[3]);
}

std::vector<RecognitionResult> Detector::detect(std::shared_ptr<VirtualImage> image) {
  // Pre process
  __preProcess(image);
  // Fill input
  if (kTfLiteOk != __fillInput(image->getWidth(), image->getHeigth(), image->getChannels(), image)) 
    throw(std::runtime_error("Image capture failed \n"));
  // Invoke 
  __interpreter->Invoke();
  // Post processing
  auto result = __postProcess(image);
  return result;
}

TfLiteStatus Detector::__fillInput(uint32_t image_width, uint32_t image_height, uint32_t channels, std::shared_ptr<VirtualImage> image) {  
  memcpy(__input->data.uint8, image->getData().data, __input->bytes);
  return kTfLiteOk;
}

std::vector<RecognitionResult> Detector::__postProcess(std::shared_ptr<VirtualImage> image) {
  std::vector<RecognitionResult> recognitions;

  // Read CNN output
  float* detection_locations = __output_detection_locations->data.f;
  float* detection_classes = __output_detection_classes->data.f;
  float* detection_scores = __output_detection_scores->data.f;
  int num_detections = (int)*__output_num_detections->data.f;
  // If the recognition exceed the score threshold is saved 
  for (int i = 0; i < num_detections; ++i) {
    if (detection_scores[i] >= __SCORE_THRESHOLD) {
      DEBUG_PRINT("detection_score: %f\n", detection_scores[i]);
      RecognitionResult recognition_result;
      recognition_result.score = detection_scores[i];
      recognition_result.label = (int)detection_classes[i];
      recognition_result.ymin = detection_locations[i * 4] * image->getHeigth();
      recognition_result.xmin = detection_locations[i * 4 + 1] * image->getWidth();
      recognition_result.ymax = detection_locations[i * 4 + 2] * image->getHeigth();
      recognition_result.xmax = detection_locations[i * 4 + 3] * image->getWidth();
      recognitions.push_back(recognition_result);
    }
  }

  return recognitions;
}

void Detector::__preProcess(std::shared_ptr<VirtualImage> image) {
  if (image->getColorSpace() != ColorSpaces(RGB)) {
    image->convertToRgb();
  }
  if (image->getWidth() != 320 || image->getHeigth() != 320) {
    image->resize(320, 320);
  }
}