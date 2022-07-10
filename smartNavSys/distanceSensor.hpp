#ifndef __DISTANCESENSOR_H__
#define __DISTANCESENSOR_H__

#include <iostream>
#include <numeric>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "common.hpp"

namespace ndistanceSensor 
{
    const int FILTER_N = 1;

};  // namespace distanceSensor 

class distanceSensor {
public:
    distanceSensor();
    ~distanceSensor();

    std::vector<int> getDistances();
    
private:
    float __timeToDistance(float time);
    void __meanOfDistances(void);
    void __readDistanceFromDriver(void);

    int __mioGpioPs;
    std::vector<int> __samples;
    std::vector<float> __sampleMean_s1;
    std::vector<float> __sampleMean_s2;
    std::vector<float> __sampleMean_s3;
};


#endif // __DISTANCESENSOR_H__