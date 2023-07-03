#include <Driver.hpp>

Driver *Driver::__instance = nullptr;

Driver *Driver::getInstance() {
  if (__instance == nullptr) {
    __instance = new Driver;
  }
  return __instance;
}

Driver::Driver() {
  int ret;

  __fd_pwm1 = open(__PWM_DRIVER_1, O_RDWR);
  if (__fd_pwm1 == -1) {
    std::stringstream err;
    err << "Could not open " << __PWM_DRIVER_1;
    throw std::runtime_error(err.str());
  }
  __fd_pwm2 = open(__PWM_DRIVER_2, O_RDWR);
  if (__fd_pwm2 == -1) {
    std::stringstream err;
    err << "Could not open " << __PWM_DRIVER_2;
    throw std::runtime_error(err.str());
  }
  __fd_l298n = open(__L298N_DRIVER, O_RDWR);
  if (__fd_l298n == -1) {
    std::stringstream err;
    err << "Could not open " << __L298N_DRIVER;
    throw std::runtime_error(err.str());
  }
  ret = ioctl(__fd_l298n, L298N_IOC_STOP);
  if ( ret == -1) 
    throw std::runtime_error("Error stopping l298n");

  __current_speed = 0;
};

Driver::~Driver() {
  ioctl(__fd_l298n, L298N_IOC_STOP);
  close(__fd_pwm1);
  close(__fd_pwm2);
  close(__fd_l298n);
};