#ifndef BA246240_9A92_4612_8A71_AC5EB85850AA
#define BA246240_9A92_4612_8A71_AC5EB85850AA

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <memory>

#include <ov7670.hpp>
#include <v_demosaic.hpp>

class CaptureFrame {
public:
  /** CaptureFrame constructor */
  CaptureFrame(uint32_t width, uint32_t height, uint32_t framerate);
  /** CaptureFrame destructor */
  ~CaptureFrame() = default; 
  /**
   * @brief Get one Frame
   * 
   * @return const cv::Mat& 
   */
  const cv::Mat& getFrame();

private:  
  /** GStreamer pipeline */
  static constexpr auto __PIPELINE{"v4l2src device=/dev/video0 ! video/x-raw, width=640, height=480, framerate=30/1 ! videoconvert ! appsink"};
  /** Video capture */
  std::shared_ptr<cv::VideoCapture> __video_capture;
  /** OV7670 object */
  std::shared_ptr<ov7670> __ov7670;
  /** v_demosaic object */
  std::shared_ptr<v_demosaic> __v_demosaic;
  /** Frame */
  cv::Mat __frame;

};


#endif /* BA246240_9A92_4612_8A71_AC5EB85850AA */
