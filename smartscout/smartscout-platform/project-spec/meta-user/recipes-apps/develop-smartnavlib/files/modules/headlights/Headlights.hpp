#ifndef CA2B04B0_85E4_4E53_82E5_BE1C95A1B194
#define CA2B04B0_85E4_4E53_82E5_BE1C95A1B194

#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#include <cstdint>
#include <stdexcept>

#define AXI_TIMER_IOC_NMAGICO 'v'
#define AXI_TIMER_IOC_T_ON _IO(AXI_TIMER_IOC_NMAGICO, 1)

class Headlights {
public:
  /** Headlights constructor */
  Headlights() {
    __fd_pwm_2 = open(__PWM_DRIVER_2, O_RDWR);
    if (__fd_pwm_2 == -1) {
      std::stringstream err;
      err << "Could not open " << __PWM_DRIVER_2;
      throw std::runtime_error(err.str());
    }
    __fd_pwm_3 = open(__PWM_DRIVER_3, O_RDWR);
    if (__fd_pwm_3 == -1) {
      std::stringstream err;
      err << "Could not open " << __PWM_DRIVER_3;
      throw std::runtime_error(err.str());
    }
  };
  /** Headlights destructor */
  ~Headlights() = default;
  /**
   * @brief Update the headlight value
   * 
   * @param value 
   */
  void update(uint32_t value) {
    int ret;

    if (value > __MAX_VALUE)
      value = __MAX_VALUE;
    else if (value < __MIN_VALUE)
      value = __MIN_VALUE;
    // Set duty cycle 
    ret = ioctl(__fd_pwm_2, AXI_TIMER_IOC_T_ON, value);
    if ( ret == -1) 
      throw std::runtime_error("Error setting duty cycle");
    // Set duty cycle 
    ret = ioctl(__fd_pwm_3, AXI_TIMER_IOC_T_ON, value);
    if ( ret == -1) 
      throw std::runtime_error("Error setting duty cycle");
  };

private:
  /** AXI Timer driver */
  static constexpr auto __PWM_DRIVER_2 {"/dev/axi_timer_pwm_2"};
  /** AXI Timer driver */
  static constexpr auto __PWM_DRIVER_3 {"/dev/axi_timer_pwm_3"};
  /** Max value */
  const int __MAX_VALUE = 100;
  /** Min value */
  const int __MIN_VALUE = 0;
  /** Headlight value (percent) */
  uint32_t __value;
  /** File descriptor of AXI Timer driver */
  int __fd_pwm_2;
  /** File descriptor of AXI Timer driver */
  int __fd_pwm_3;

};




#endif /* CA2B04B0_85E4_4E53_82E5_BE1C95A1B194 */
