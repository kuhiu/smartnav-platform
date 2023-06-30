#ifndef A5A33ABE_E8AC_4A84_BAEE_383996A34736
#define A5A33ABE_E8AC_4A84_BAEE_383996A34736

#include <string>
#include <memory>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

class CameraSender {
public:
  /** CameraSender constructor */
  CameraSender(uint32_t width, uint32_t height, uint32_t framerate, std::string ip, std::string port) 
     : __PIPELINE(std::string("appsrc ! videoconvert " \
                        "! x264enc tune=zerolatency speed-preset=ultrafast " \
                        "! rtph264pay " \
                        "! udpsink") + " host=" + ip + " port=" + port) { 
    __writer = std::make_unique<cv::VideoWriter>( __PIPELINE.c_str(), 
                                                  cv::CAP_GSTREAMER,
                                                  0,		// fourcc 
                                                  framerate,		// fps
                                                  cv::Size(width, height), 
                                                  true);	// isColor
    if (!__writer->isOpened()) 
      throw std::runtime_error("ERROR! Unable to open the VideoWriter");
  };
  /** CameraSender destructor */
  ~CameraSender() = default;
  /**
   * @brief Send the frame
   * 
   * @param frame 
   */
  void send(const cv::Mat& frame) {
    __writer->write(frame);
  }


private:
  /** GStreamer pipeline */
  const std::string __PIPELINE;
  /** VideoWriter */
  std::unique_ptr<cv::VideoWriter> __writer;

};



#endif /* A5A33ABE_E8AC_4A84_BAEE_383996A34736 */
