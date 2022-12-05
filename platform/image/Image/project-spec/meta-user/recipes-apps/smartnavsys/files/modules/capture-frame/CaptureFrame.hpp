/** This module is responsable of open, init, and use a v4l2 device driver 
 * author: Fuschetto Martin
 * email: marfus@hotmail.es 
 * date: 15/11/22
 * version: 0.0
*/

#ifndef __CAPTUREFRAME_H__
#define __CAPTUREFRAME_H__

#include <sys/stat.h>
#include <linux/videodev2.h>

#include <atomic>
#include <functional>
#include <thread>

#include "../logger/Logger.hpp"

class CaptureFrame {
public:
  /** Image buffer */
  struct ImageBuffer {
    void* start[VIDEO_MAX_PLANES];
    size_t  length[VIDEO_MAX_PLANES];
    v4l2_plane planes[VIDEO_MAX_PLANES];
  };
  enum pixelFormat {
    PIX_FMT_RGB24 = 0,

  };
  /** Callback of captured frame */
  using EventCallback = std::function<void (void* data, unsigned int size)>;
  /** CaptureFrame constructor */
  CaptureFrame(EventCallback cb, uint32_t width, uint32_t height, pixelFormat pixel_format, uint32_t frame_count = 1);
  /** CaptureFrame destructor */
  ~CaptureFrame();

private:
  /** Clear vl2d struct */
  #define CLEAR(x) memset(&(x), 0, sizeof(x))
  /** Device name */
  static constexpr const char *__DEVICE = {"/dev/video0"};
  /** Device file descriptor */
  int __fd;
  /** Device driver stats */
  struct stat __st;
	/** Device capabilities */ 
	v4l2_capability __capability;
  /** Image buffers */
  std::vector<ImageBuffer> __image_buffers;
  /** Format */
	v4l2_format __format;
  /** Numbers of planes for image buffer */
  const int __num_planes = 1;
  /** Driver type */
  int __driver_type;
  /** Buffer type */
  int __buffer_type;
  /** V4L2 stream parameter */
  v4l2_streamparm __parm;
  /** V4L2 request buffers */
  v4l2_requestbuffers __req;
  /** Capture Callback */
  const EventCallback __cb;
  /** Thread status */
  bool __capture_frame_is_running;
  /** Execution thread for captures */
  std::thread __capture_thread;
  /** Frame count to capture */
  const uint32_t __frame_count;
  /** Open device driver */
  void __openDevice();
  /** Close device driver */
  void __closeDevice();
  /** Init device */
  void __initDevice(uint32_t width, uint32_t height, pixelFormat pixelformat);
  /** Uninit device*/
  void __uninitDevice();
  /** Set format */
  void __setFormat(uint32_t width, uint32_t height, pixelFormat pixel_format);
  /** Get format */
  void __getFormat();
  /** Set the framerate */
  void __setFramerate();
  /**
   * @brief Initialize fields
   * 
   * @param field Field to be initialized 
   */
  void __setField(v4l2_pix_format_mplane &field, uint32_t width, uint32_t height, pixelFormat pixel_format);
  /** Start capturing frames */
  void __startCapturing();
  /** Read frame */
  bool __readFrame(int frame_number);
  /** Capture frame */
  void __capture();
  /**
   * @brief ioctl wrapper
   * 
   * @param fd File descriptor 
   * @param request ioctl request 
   * @param arg arguments
   * @return int 
   */
  int __xioctl(int fd, int request, void* arg);
  /** Init mmap */
  void __init_mmap();

};



#endif // __CAPTUREFRAME_H__