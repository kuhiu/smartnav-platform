#include <CaptureFrame.hpp>

CaptureFrame *CaptureFrame::__instance = nullptr;

CaptureFrame *CaptureFrame::getInstance(uint32_t width, uint32_t height) {
  if (__instance == nullptr) {
    __instance = new CaptureFrame(width, height);
  }
  return __instance;
}

const cv::Mat CaptureFrame::getFrame() {
  cv::Mat frame;

  __video_capture.read(frame);
  if (frame.empty()) {
    throw std::runtime_error("The frame could not be readed");
  }
  return frame;
}
