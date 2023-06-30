#ifndef D7188A15_EEE0_4F97_B963_7AB4A1EB47DA
#define D7188A15_EEE0_4F97_B963_7AB4A1EB47DA

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <buttons.h>
#include <string.h>
#include <sys/ioctl.h>

#include <sstream>

class Buttons {  
public:
  /** Buttons constructor */
  Buttons() {
    __fd = open(__DRIVER, O_RDWR);
    if (__fd < 0) {
      std::ostringstream err;
      err << "Open failed:" << strerror(errno); 
      throw std::runtime_error(err.str());
    }
  };
  /** Buttons destructor */
  ~Buttons() {
    close(__fd);
  };
  /**
   * @brief Read the button and return the status
   * 
   * @param button_num 
   * @return int 
   */
  ButtonNum read() {
    int err;
    ButtonNum ret = ButtonNum::NON_EXISTENT;

    err = ioctl(__fd, BUTTONS_IOC_WAIT_BLOCKING, &ret);
    printf("Hola.\n");
    if (err < 0) {
      printf("Ioctl failed: %s", strerror(errno));
      return ButtonNum::NON_EXISTENT;
    }
    printf("The button pressed is %d.\n", ret);
    return ret;
  };

private:
  /** Driver name */
  static constexpr const char* __DRIVER{"/dev/buttons"}; 
  /** File descriptor */
  int __fd;

};

#endif /* D7188A15_EEE0_4F97_B963_7AB4A1EB47DA */
