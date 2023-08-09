#ifndef BA246240_9A92_4612_8A71_AC5EB85850AA
#define BA246240_9A92_4612_8A71_AC5EB85850AA

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

class CaptureFrame {
public:
  /**
   * @brief Get the Instance of the WebServer
   * 
   * @return WebServer* 
   */
  static CaptureFrame* getInstance(uint32_t width, uint32_t height);
  /**
   * @brief Deleting copy constructor 
   * 
   */
  CaptureFrame(const CaptureFrame& obj) = delete;
  /**
   * @brief Singleton should not be assignable
   * 
   */
  void operator=(const CaptureFrame&) = delete;
  /**
   * @brief Get one Frame
   * 
   * @return const cv::Mat& 
   */
  const cv::Mat getFrame();

private:  
  /** Singleton instance */
  static CaptureFrame* __instance;
  /** Camera device number */
  const int __DEVICE_ID = 0; 
  /** Device APIs id */
  const int __API_ID = cv::CAP_V4L2;
  /** Video capture */
  cv::VideoCapture __video_capture;
  /** CaptureFrame constructor */
  CaptureFrame(uint32_t width, uint32_t height) {
    // Init video capture 
    __video_capture.open(__DEVICE_ID);
    if(!__video_capture.isOpened()) 
      throw std::runtime_error("Retry to open the video capture");
    __video_capture.set(cv::CAP_PROP_FRAME_WIDTH, width);
    __video_capture.set(cv::CAP_PROP_FRAME_HEIGHT, height);
  };
  /** CaptureFrame destructor */
  ~CaptureFrame() = default; 

};


#endif /* BA246240_9A92_4612_8A71_AC5EB85850AA */
