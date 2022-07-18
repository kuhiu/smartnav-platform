#ifndef __DRIVER_H__
#define __DRIVER_H__

#include <sstream>
#include <string>
#include <map>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <ioConfig.hpp>

class driver {
public:
    /**
     * @brief Construct a new driver object
     * 
     * @param inputs Wait for the next map 
     * 
     * std::map<std::string, float> inputs { 
     *  {output::NAME, value},
     *  ...
     *  {output::NAME, value} };
     * 
     */
    driver();

    /** Destroy the driver object */
    ~driver();

    void drive(const std::map<std::string, float> inputs);
    
private:
    static constexpr auto PWM1_DRIVER = "/dev/chardev_pwm_EMIOgpio_PL_1";
    static constexpr auto PWM2_DRIVER = "/dev/chardev_pwm_EMIOgpio_PL_2";
    static constexpr auto GPIO_DRIVER = "/dev/chardev_EMIOgpio_PL";
    static constexpr auto BYTE2READ   = 1*sizeof(int);
    static constexpr auto GO_FORWARD  = ((0x1<<0) | (0x0<<1) | (0x1<<2) | (0x0<<3)); 
    static constexpr auto STOP        = ((0x0<<0) | (0x0<<1) | (0x0<<2) | (0x0<<3));
    static constexpr auto GO_TO_RIGHT = ((0x1<<0) | (0x0<<1) | (0x0<<2) | (0x1<<3));
    static constexpr auto GO_TO_LEFT  = ((0x0<<0) | (0x1<<1) | (0x1<<2) | (0x0<<3)); 
    static constexpr auto GO_BACK     = ((0x0<<0) | (0x1<<1) | (0x0<<2) | (0x1<<3)); 
    static constexpr auto MAX_SPEED   = 25;
    int __pwm1;
    int __pwm2;
    int __emioGpio;  
    float __speed;
};

#endif // __DRIVER_H__