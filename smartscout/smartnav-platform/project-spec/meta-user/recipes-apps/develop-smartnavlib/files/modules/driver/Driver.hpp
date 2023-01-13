#ifndef CCFCEC50_F647_4011_8C90_12D85406C31B
#define CCFCEC50_F647_4011_8C90_12D85406C31B

class Driver {
public:
  /** Driver constructor */
  Driver() {
    if ()
  };
  /** Driver destructor */
  ~Driver();

  void update();

private:
  /** AXI Timer driver */
  static constexpr auto __PWM_DRIVER_1 {"/dev/pwm_1"};
  /** AXI Timer driver */
  static constexpr auto __PWM_DRIVER_1 {"/dev/pwm_2"};
  /** L298N driver */
  static constexpr auto __L298N_DRIVER {"/dev/pwm_2"};
  /** File descriptor of AXI Timer driver */
  int __fd_pwm1;
  /** File descriptor of AXI Timer driver */
  int __fd_pwm2;
  /** File descriptor of L298N driver */
  int __emioGpio;  
  
};




#endif /* CCFCEC50_F647_4011_8C90_12D85406C31B */
