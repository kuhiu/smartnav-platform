#ifndef BA246240_9A92_4612_8A71_AC5EB85850AA
#define BA246240_9A92_4612_8A71_AC5EB85850AA

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

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
  const cv::Mat& getFrame();

private:  
  /** Singleton instance */
  static CaptureFrame* __instance;
  /** Image width */
  const int __IMG_WIDTH;
  /** Image height */
  const int __IMG_HEIGHT;
  /** Image channel */
  static const int __IMG_CHANNELS{4};
  /** Physical VDMA dir */
  static constexpr off_t __READ_OFFSET{0x01000000};
  static constexpr off_t __WRITE_OFFSET{0x02000000};
  /** Memory file descriptor */
  int __memFd;
  /** Read memory */
  void *__readBuffer;
  /** Write memory */
  void *__writeBuffer;
  /** Virtual image */
  cv::Mat __image;
  /** BRG image */
  cv::Mat __img_bgr;
  /** CaptureFrame constructor */
  CaptureFrame(uint32_t width, uint32_t height);
  /** CaptureFrame destructor */
  ~CaptureFrame();

};


#endif /* BA246240_9A92_4612_8A71_AC5EB85850AA */
