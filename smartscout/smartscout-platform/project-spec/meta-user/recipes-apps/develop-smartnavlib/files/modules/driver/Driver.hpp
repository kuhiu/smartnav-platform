#ifndef CCFCEC50_F647_4011_8C90_12D85406C31B
#define CCFCEC50_F647_4011_8C90_12D85406C31B

#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#include <atomic>
#include <cmath>
#include <sstream>
#include <stdexcept>

#define L298N_IOC_NMAGICO 'c'
#define L298N_IOC_STOP _IO(L298N_IOC_NMAGICO, 0)
#define L298N_IOC_FORWARD _IO(L298N_IOC_NMAGICO, 1)
#define L298N_IOC_BACK _IO(L298N_IOC_NMAGICO, 2)
#define L298N_IOC_RIGHT _IO(L298N_IOC_NMAGICO, 3)
#define L298N_IOC_LEFT _IO(L298N_IOC_NMAGICO, 4)

#define AXI_TIMER_IOC_NMAGICO 'v'
#define AXI_TIMER_IOC_T_ON _IO(AXI_TIMER_IOC_NMAGICO, 1)

class Driver {
public:
  enum operationMode {
    /** Stop */
    OP_STOP = 0,
    /** Drive */
    OP_DRIVE,

  };
  /** Actual estimated position*/
  struct position {
    /** Actual x estimated position */
    int x;
    /** Actual y estimated position */
    int y;

  };
  /**
   * @brief Get the Instance of the Driver
   * 
   * @return WebServer* 
   */
  static Driver* getInstance();
  /**
   * @brief Deleting copy constructor
   * 
   * @param obj 
   */
  Driver(const Driver& obj) = delete;
  /**
   * @brief Singleton should not be assignable
   * 
   */
  void operator=(const Driver&) = delete;
  /**
   * @brief Get the Speed 
   * 
   * @return int 
   */
  int getSpeed() const { return __current_speed.load(); }
  /**
   * @brief Update the pwms that control both motors
   * 
   * @param pwm0
   * @param pwm1 
   */
  void update_pwm(int pwm0, int pwm1) {
    int ret;

    // Set duty cycle 
    ret = ioctl(__fd_pwm1, AXI_TIMER_IOC_T_ON, pwm0);
    if ( ret == -1) 
      throw std::runtime_error("Error setting duty cycle");
    // Set duty cycle 
    ret = ioctl(__fd_pwm2, AXI_TIMER_IOC_T_ON, pwm1);
    if ( ret == -1) 
      throw std::runtime_error("Error setting duty cycle");
    // Go forward
    ret = ioctl(__fd_l298n, L298N_IOC_FORWARD);
    if ( ret == -1) 
      throw std::runtime_error("Error stopping l298n");
  }
  /**
   * @brief Update the speed and yaw for driving the car
   * 
   * @param operation_mode 
   * @param speed_variation 
   * @param yaw_variation 
   */
  void update(operationMode operation_mode, int speed_variation, int yaw_variation) {
    int ret;
    int wheel_left;
    int wheel_right;
    int direction;
    
    // Protection: baterry consumption 
    if (speed_variation > 20)
      throw std::runtime_error("The speed variation was so big");

    __current_speed.fetch_add(speed_variation);
    __current_yaw += yaw_variation;
    // Check for max and min of the yaw 
    if (__current_yaw > __MAX_YAW)
      __current_yaw = __MAX_YAW;
    else if (__current_yaw < __MIN_YAW)
      __current_yaw = __MIN_YAW;
    // Check for max and min of the speed 
    if (__current_speed.load() > __MAX_SPEED)
      __current_speed.store(__MAX_SPEED);
    else if (__current_speed < __MIN_SPEED)
      __current_speed = __MIN_SPEED;
    
    //printf("Current speed %d, Current yaw %d.\n", __current_speed.load(), __current_yaw);
    // Wheel PWM 
    wheel_left = __current_speed.load() - __current_yaw;
    wheel_right = __current_speed.load() + __current_yaw;
    // Check for max of the pwm duty cycle 
    if (wheel_left > __MAX_DUTY) 
      wheel_left = __MAX_DUTY;
    else if (wheel_left < __MIN_DUTY)
      wheel_left = __MIN_DUTY;
    // Check for max of the pwm duty cycle 
    if (wheel_right > __MAX_DUTY) 
      wheel_right = __MAX_DUTY;
    else if (wheel_right < __MIN_DUTY)
      wheel_right = __MIN_DUTY;
    // Set direction 
    if ((wheel_left > 0) && (wheel_right > 0))
      direction = L298N_IOC_FORWARD;
    else if ((wheel_left < 0) && (wheel_right < 0))
      direction = L298N_IOC_BACK;
    else if ((wheel_left < 0) && (wheel_right > 0))
      direction = L298N_IOC_LEFT;
    else if ((wheel_left > 0) && (wheel_right < 0))
      direction = L298N_IOC_RIGHT;
    else 
      direction = L298N_IOC_STOP;
    // Set duty cycle 
    ret = ioctl(__fd_pwm1, AXI_TIMER_IOC_T_ON, std::abs(wheel_left));
    if ( ret == -1) 
      throw std::runtime_error("Error setting duty cycle");
    // Set duty cycle 
    ret = ioctl(__fd_pwm2, AXI_TIMER_IOC_T_ON, std::abs(wheel_right));
    if ( ret == -1) 
      throw std::runtime_error("Error setting duty cycle");
    // Set direction 
    switch (operation_mode) {
    case OP_STOP:
      // Reset current speed 
      __current_speed.store(0);
      ret = ioctl(__fd_l298n, L298N_IOC_STOP);
      if ( ret == -1) 
        throw std::runtime_error("Error stopping l298n");
      break;
    case OP_DRIVE:
      ret = ioctl(__fd_l298n, direction);
      if ( ret == -1) 
        throw std::runtime_error("Error going forward l298n");
      break;
    default:
      throw std::runtime_error("Driver: operation not supported.");
      break;
    }
  };

private:
  /** AXI Timer driver */
  static constexpr auto __PWM_DRIVER_1 {"/dev/axi_timer_pwm_0"};
  /** AXI Timer driver */
  static constexpr auto __PWM_DRIVER_2 {"/dev/axi_timer_pwm_1"};
  /** L298N driver */
  static constexpr auto __L298N_DRIVER {"/dev/l298n"};
  /** Max speed */
  const int __MAX_SPEED = 85;
  /** Min speed */
  const int __MIN_SPEED = -85;
  /** Max duty cycle */
  const int __MAX_DUTY = 100;
  /** Min duty cycle */
  const int __MIN_DUTY = -100;
  /** Max yaw */
  const int __MAX_YAW = 15;
  /** Min yaw */
  const int __MIN_YAW = -15;
  /** File descriptor of AXI Timer driver */
  int __fd_pwm1;
  /** File descriptor of AXI Timer driver */
  int __fd_pwm2;
  /** File descriptor of L298N driver */
  int __fd_l298n;  
  /** Current speed */
  std::atomic<int> __current_speed;
  /** Current yaw */
  int __current_yaw;
  /** Singleton instance */
  static Driver* __instance;
  /** Driver constructor */
  Driver();
  /** Driver destructor */
  ~Driver();

};




#endif /* CCFCEC50_F647_4011_8C90_12D85406C31B */
