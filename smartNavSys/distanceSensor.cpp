#include "distanceSensor.hpp"

distanceSensor::distanceSensor() {
    std::ostringstream err;

    if ( (__mioGpioPs = open(MIOGPIOPS, O_RDONLY)) == -1){
        err << "__mioGpioPs fail";
        throw std::runtime_error(err.str());
    }

    __samples = {0,0,0};
    __sampleMean_s1 = {0.0, 0.0, 0.0};
    __sampleMean_s2 = {0.0, 0.0, 0.0};
    __sampleMean_s3 = {0.0, 0.0, 0.0};
}

distanceSensor::~distanceSensor() {
    close(__mioGpioPs);
}

std::vector<int> distanceSensor::getDistances() {
    distanceSensor::__readDistanceFromDriver();
    distanceSensor::__meanOfDistances();
    return __samples;
}
    
float distanceSensor::__timeToDistance(float time) {
    float distance = time*(float)0.01715;

    if ( (distance > 500) || (distance < 0) )
        return 500;
    return distance;    
}

void distanceSensor::__meanOfDistances(void) {
    std::ostringstream err;
    if (__sampleMean_s1.empty() ) {
        err << "__sampleMean_s1 empty ";
        throw std::runtime_error(err.str());
    }
    if (__sampleMean_s2.empty() ) {
        err << "__sampleMean_s2 empty ";
        throw std::runtime_error(err.str());
    }
    if (__sampleMean_s3.empty() ) {
        err << "__sampleMean_s3 empty ";
        throw std::runtime_error(err.str());
    }
    __samples[0] = std::accumulate(__sampleMean_s1.begin(), __sampleMean_s1.end(), 0.0) / __sampleMean_s1.size();
    __samples[1] = std::accumulate(__sampleMean_s2.begin(), __sampleMean_s2.end(), 0.0) / __sampleMean_s2.size();
    __samples[2] = std::accumulate(__sampleMean_s3.begin(), __sampleMean_s3.end(), 0.0) / __sampleMean_s3.size();

    __sampleMean_s1.clear();
    __sampleMean_s1.shrink_to_fit();
    __sampleMean_s2.clear();
    __sampleMean_s2.shrink_to_fit();
    __sampleMean_s3.clear();
    __sampleMean_s3.shrink_to_fit();
}

void distanceSensor::__readDistanceFromDriver(void) {
    int i;
    int rb_MIOgpio_PS[N_MIOGPIOPS];

    for( i=ndistanceSensor::FILTER_N ; i>0 ; i-- ){
        if ( read(__mioGpioPs, rb_MIOgpio_PS, N_MIOGPIOPS*sizeof(int)) == -1){
            throw MIOGPIOPS;
        }
        __sampleMean_s1.push_back(__timeToDistance((float)rb_MIOgpio_PS[0]));
        __sampleMean_s2.push_back(__timeToDistance((float)rb_MIOgpio_PS[1]));
        __sampleMean_s3.push_back(__timeToDistance((float)rb_MIOgpio_PS[2]));
    }
}