#ifndef B77A5245_E8C7_4369_BDBB_EA590ED10914
#define B77A5245_E8C7_4369_BDBB_EA590ED10914

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <mailbox.h>
#include <unistd.h>

class mailbox {
public:
  enum command {
    /** Get encoder count */
    ENCODER_1_COUNT = 1,
    /** Get encoder count */
    ENCODER_2_COUNT = 2,
    /** Led control */
    LED_CTRL = 3,

  };
  /** Mailbox constructor */
  mailbox() {
    __fd = open(__DRIVER, O_RDWR);
    if (__fd < 0) {
      std::ostringstream err;
      err << "Open failed:" << strerror(errno); 
      throw std::runtime_error(err.str());
    }
  };
  /** Mailbox destructor */
  ~mailbox() {
    close(__fd);
  };
  /**
   * @brief Send a command to the mailbox
   * 
   * @param cmd 
   * @param arg 
   */
  int sendBlocking(command cmd, int arg) {
    int ret = 0;
    msg_mailbox msg;

    msg.msg[0] = __START_STREAM;
    msg.msg[1] = cmd;
    msg.msg[2] = arg;
    msg.msg[3] = __END_STREAM;
    ret = ioctl(__fd, AXI_MAILBOX_IOC_PUSH_BLOCKING, &msg);
    if (ret < 0) {
        printf("Ioctl failed: %s", strerror(errno));
        return ret;
    }
    return ret;
  };
  /**
   * @brief Read a msg from the mailbox
   * 
   * @return int 
   */
  int receiveBlocking() {
    int ret = 0;
    msg_mailbox msg;

    ret = ioctl(__fd, AXI_MAILBOX_IOC_POP_BLOCKING, &msg);
    if (ret < 0) {
        printf("Ioctl failed: %s", strerror(errno));
        return ret;
    }
    return msg.msg[2];
  };

private:
  /** Driver */
  static constexpr const char* __DRIVER = {"/dev/axi_mailbox_0"}; 
  /** File descriptor */
  int __fd;
  /** Start of the stream protocol */
  const int __START_STREAM = 0xAA;
  /** End of the stream protocol */
  const int __END_STREAM = 0x55;

};

#endif /* B77A5245_E8C7_4369_BDBB_EA590ED10914 */
