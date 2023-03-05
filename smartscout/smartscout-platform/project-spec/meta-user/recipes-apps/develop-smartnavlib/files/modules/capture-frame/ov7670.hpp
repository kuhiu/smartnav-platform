#ifndef DD65BE71_A52D_4007_B819_2996018A875D
#define DD65BE71_A52D_4007_B819_2996018A875D

#include <errno.h>
#include <linux/videodev2.h>
#include <sys/ioctl.h>
#include <sys/stat.h>

#include <cstdint>

#include <linux/v4l2-subdev.h>

class ov7670 {
public:
  /** Pixel formats supported */
  enum pixelFormat {
    SBGGR8_1X8 = 0,

  };
  /** ov7670 constructor */
  ov7670(uint32_t width, uint32_t height, pixelFormat pixel_format, uint32_t frame_rate);
  /** ov7670 destructor */
  ~ov7670();

private:
  /** Clear vl2d struct */
  #define CLEAR(x) memset(&(x), 0, sizeof(x))
  /** Device name */
  static constexpr const char *__DEVICE = {"/dev/v4l-subdev0"};
  /** Device file descriptor */
  int __fd;
  /** Device driver stats */
  struct stat __st;
  /** Open ov7670 driver */
  void __openDevice();
  /** Close ov7670 driver */
  void __closeDevice();

  void __initDevice(uint32_t width, uint32_t height, pixelFormat pixelformat, uint32_t frame_rate);

  void __setFramerate(uint32_t frame_rate);

  void __setFormat(uint32_t width, uint32_t height, pixelFormat pixelformat);
  /**
   * @brief Ioctl wrapper
   * 
   * @param fd 
   * @param request 
   * @param arg 
   * @return int 
   */
  int __xioctl(int fd, int request, void *arg) {
    int r;
    do {
      r = ioctl(fd, request, arg);
    } while (-1 == r && EINTR == errno);

    return r;
  }
	/** Frame interval */ 
	v4l2_subdev_frame_interval __frame_interval;
  /** Format */
	v4l2_subdev_format __format;

};



#endif /* DD65BE71_A52D_4007_B819_2996018A875D */
