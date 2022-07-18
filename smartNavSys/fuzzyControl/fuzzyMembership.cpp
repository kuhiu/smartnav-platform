#include <fuzzyMembership.hpp>

void fuzzyMembership::initializer(const std::string &name, float point1, float point2, float slope1, float slope2) {
    __name = name; 
    __value = 0.0;
    __point1 = point1;
    __point2 = point2;
    __slope1 = slope1;
    __slope2 = slope2;
}


float fuzzyMembership::getValue(void) const {
    return __value;
}

float fuzzyMembership::getPoint1(void) const{
    return __point1;
}
float fuzzyMembership::getPoint2(void) const {
    return __point2;
}
float fuzzyMembership::getSlope1(void) const {
    return __slope1;
}
float fuzzyMembership::getSlope2(void) const {
    return __slope2;
}

void fuzzyMembership::setValue(float value) {
    __value = value;
}

const std::string &fuzzyMembership::getName(void) const {
    return __name;
}