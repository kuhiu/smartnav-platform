#ifndef CB5B5C1C_6F80_4596_BF70_05BE5FF31EA5
#define CB5B5C1C_6F80_4596_BF70_05BE5FF31EA5

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <iostream>
#include <stdexcept>

class VdmaController {
public:
  /** VdmaController constructor */
  VdmaController() {
    __fd = open("/dev/vdma_control_chardev", O_RDWR);
    if (__fd == -1) 
      throw std::runtime_error("Error opening VDMA driver");

  };
  /** VdmaController destructor */
  ~VdmaController() {
    close(__fd);
  };

  private:
  /** VDMA file desciptor */
  int __fd;

};

#endif /* CB5B5C1C_6F80_4596_BF70_05BE5FF31EA5 */