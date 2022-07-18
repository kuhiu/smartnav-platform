#include <driver.hpp>

driver::driver() {
    int newPwm = 0;
    std::ostringstream err;
    __speed = 0;
    
    if ( (__emioGpio = open(GPIO_DRIVER, O_RDWR)) == -1){
        err << "Open " << GPIO_DRIVER << " fail";
        throw std::runtime_error(err.str());
    }

    if ( (__pwm1 = open(PWM1_DRIVER, O_RDWR)) == -1){
        err << "Open " << PWM1_DRIVER << " fail";
        throw std::runtime_error(err.str());
    }

    if ( (__pwm2 = open(PWM2_DRIVER, O_RDWR)) == -1){
        err << "Open " << PWM2_DRIVER << " fail";
        throw std::runtime_error(err.str());
    }

    if ( ( write(__pwm1, &newPwm, BYTE2READ)) == -1){
        err << "Error writing " << PWM1_DRIVER;
        throw std::runtime_error(err.str());
    }
    if ( ( write(__pwm2, &newPwm, BYTE2READ)) == -1){
        err << "Error writing " << PWM2_DRIVER;
        throw std::runtime_error(err.str());
    }
    int go = driver::GO_FORWARD;
    if ( ( write(__emioGpio, &go, BYTE2READ)) == -1){
        err << "Error writing " << GPIO_DRIVER;
        throw std::runtime_error(err.str());
    }
}

driver::~driver() {
    int newPwm = 0;
    std::ostringstream err;
    if ( ( write(__pwm1, &newPwm, BYTE2READ)) == -1){
        err << "Error writing " << PWM1_DRIVER;
        throw std::runtime_error(err.str());
    }
    if ( ( write(__pwm2, &newPwm, BYTE2READ)) == -1){
        err << "Error writing " << PWM2_DRIVER;
        throw std::runtime_error(err.str());
    }
    int go = driver::STOP;
    if ( ( write(__emioGpio, &go, BYTE2READ)) == -1){
        err << "Error writing " << GPIO_DRIVER;
        throw std::runtime_error(err.str());
    }
    close(__emioGpio);
    close(__pwm1);
    close(__pwm2);
}

void driver::drive(const std::map<std::string, float> inputs) {
    std::map<std::string, float>::const_iterator pos;
    std::ostringstream err;
    float heading;
    float speedVariation;
    float whereToGo;
    int newPwm1;
    int newPwm2;

    pos = inputs.find(out_heading::NAME); 
    if (pos == inputs.end()) {
        err << "No " << out_heading::NAME << " was found";
        throw std::runtime_error(err.str());
    }
    else {
        heading = pos->second;
    }
    pos = inputs.find(out_speed::NAME);
    if (pos == inputs.end()) {
        err << "No " << out_speed::NAME << " was found";
        throw std::runtime_error(err.str());
    }
    else {
        speedVariation = pos->second;
    }
    pos = inputs.find(in_ov7670::NAME);
    if (pos == inputs.end()) {
        err << "No " << in_ov7670::NAME << " was found";
        throw std::runtime_error(err.str());
    }
    else {
        whereToGo = pos->second;
    }
    printf("driver:: whereToGo %f\n", whereToGo);
    printf("driver:: speedVariation %f\n", speedVariation);
    printf("driver:: heading %f\n", heading);
    if (whereToGo < 0) { /* imgProc module: invalid output */
        int newPwm = 0;
        std::ostringstream err;
        if ( ( write(__pwm1, &newPwm, BYTE2READ)) == -1){
            err << "Error writing " << PWM1_DRIVER;
            throw std::runtime_error(err.str());
        }
        if ( ( write(__pwm2, &newPwm, BYTE2READ)) == -1){
            err << "Error writing " << PWM2_DRIVER;
            throw std::runtime_error(err.str());
        }
        return;
    }
    __speed += speedVariation;
    /* Guard */
    if (__speed > MAX_SPEED)
        __speed = MAX_SPEED;
    else if (__speed < 0)
        __speed = 0;
    newPwm1 = __speed - heading;
    newPwm2 = __speed + heading;
    printf("driver:: newPwm1 %d\n", newPwm1);
    printf("driver:: newPwm2 %d\n", newPwm2);
    printf("driver:: __speed %f\n", __speed);
    if ( ( write(__pwm1, &newPwm1, BYTE2READ)) == -1){
        err << "Error writing " << PWM1_DRIVER;
        throw std::runtime_error(err.str());
    }
    if ( ( write(__pwm2, &newPwm2, BYTE2READ)) == -1){
        err << "Error writing " << PWM2_DRIVER;
        throw std::runtime_error(err.str());
    }
}