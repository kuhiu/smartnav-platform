#ifndef C9FEF92A_4968_472F_8933_806403749BA9
#define C9FEF92A_4968_472F_8933_806403749BA9

#include <errno.h>
#include <linux/videodev2.h>
#include <sys/ioctl.h>
#include <sys/stat.h>

#include <cstdint>

#include <linux/v4l2-subdev.h>

class v_demosaic {
public:
  /** Pixel formats supported */
  enum pixelFormat {
    RBG888_1X24 = 0,

  };
  /** ov7670 constructor */
  v_demosaic(uint32_t width, uint32_t height, pixelFormat pixel_format);
  /** ov7670 destructor */
  ~v_demosaic();

private:
  /** Clear vl2d struct */
  #define CLEAR(x) memset(&(x), 0, sizeof(x))
  /** Device name */
  static constexpr const char *__DEVICE = {"/dev/v4l-subdev1"};
  /** Device file descriptor */
  int __fd;
  /** Device driver stats */
  struct stat __st;
  /** Open ov7670 driver */
  void __openDevice();
  /** Close ov7670 driver */
  void __closeDevice();

  void __initDevice(uint32_t width, uint32_t height, pixelFormat pixelformat);

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
  /** Format */
	v4l2_subdev_format __format;

};

#endif /* DD65BE71_A52D_4007_B819_2996018A875D */

