#ifndef __SMARtNAVSYS_H__
#define __SMARtNAVSYS_H__

#include <vector>
#include <signal.h>
#include <sys/time.h>
#include <map>
#include <set>

#include "imgProc.hpp"
#include "distanceSensor.hpp"
#include "fuzzyControl.hpp"
#include <smartNavSys.hpp>
#include "driver.hpp"
#include "common.hpp"

class smartNavSys {
public:
    smartNavSys();
    ~smartNavSys() = default;

    void run(void);
private:
    /* modules */
    distanceSensor __distanceSensor;
    driver __driver;
    fuzzyControl __fuzzyControl;
    imgProc __imgProc;
    //common __common;
    /* Distance sensors data */
    std::vector<int> __sensorData;
    /* Inputs of driver */
    std::map<std::string, float> __driverInputsMap;
    /* Inputs of fuzzy control system */
    std::map<std::string, int> __fuzzyInputsMap;
};




#endif // __SMARtNAVSYS_H__