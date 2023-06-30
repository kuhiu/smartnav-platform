#include <CaptureFrame.hpp>

constexpr const char* CaptureFrame::__PIPELINE;

CaptureFrame::CaptureFrame(uint32_t width, uint32_t height, uint32_t framerate) {
  uint32_t retries = 3;

  // Init v4l2 devices
  __ov7670 = std::make_shared<ov7670>(width, height, ov7670::pixelFormat::SBGGR8_1X8, framerate);
  __v_demosaic = std::make_shared<v_demosaic>(width, height, v_demosaic::pixelFormat::RBG888_1X24);
  // Init video capture 
  __video_capture = std::make_shared<cv::VideoCapture>(__PIPELINE, cv::CAP_GSTREAMER);
  while((!__video_capture->isOpened()) && (retries > 0)) {
    __video_capture->open(__PIPELINE, cv::CAP_GSTREAMER);
    std::cout << "Retry to open the video capture" << std::endl;
    retries--;
  }
  // If the video capture could not be opened failed.
  if(!__video_capture->isOpened()) {
    throw std::runtime_error("Video Capture could not be opened.");
  }
};

const cv::Mat& CaptureFrame::getFrame() {
  __video_capture->read(__frame);
  if (__frame.empty()) {
    throw std::runtime_error("The frame could not be readed");
  }
  return __frame;
}
