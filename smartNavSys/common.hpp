#ifndef __COMMON_H__
#define __COMMON_H__

#include <mutex>
#include <sstream>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>

#define DEBUG

#ifdef DEBUG 
#define DEBUG_PRINT(x) printf x
#else
#define DEBUG_PRINT(x) do {} while (0)
#endif 

namespace nCommon 
{
    constexpr const char *STATE{"state.txt"};
    constexpr const char *SENSOR1{"Sensores, rightSensor = %s"};
    constexpr const char *SENSOR2{"Sensores, centerSensor = %s"};
    constexpr const char *SENSOR3{"Sensores, leftSensor = %s"};
    constexpr const char *IMGDATA{"ImgProc, Direccion = %s"};
    constexpr const char *HEADING{"Angulo requerido = %s"};
    constexpr const char *SPEED{"Pwm, Velocidad = %s"};

};  // namespace Common 

//std::mutex m;

class common {
public:
    enum dataType{
        Sensor1,
        Sensor2,
        Sensor3,
        ImgData,
        Speed,
        Heading,
    };
    common();
    ~common();

    void saveToState(int data, enum dataType dataType);
    int readFromState(enum dataType dataType); 
private:
    std::fstream __state;

};

#endif // __COMMON_H__