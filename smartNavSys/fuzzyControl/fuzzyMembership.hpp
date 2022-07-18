#ifndef __FUZZYMEMBERSHIP_H__
#define __FUZZYMEMBERSHIP_H__

#include <string>

class fuzzyMembership {
public:
    fuzzyMembership() = default;
    ~fuzzyMembership() = default;

    void initializer(const std::string &name, float point1, float point2, float slope1, float slope2);
    float getValue(void) const;
    void setValue(float value);
    float getPoint1(void) const;
    float getPoint2(void) const;
    float getSlope1(void) const;
    float getSlope2(void) const;
    const std::string &getName(void) const;
private:
  std::string __name;       
  float __value;              
  float __point1;             
  float __point2;             
  float __slope1;             
  float __slope2;             
};

#endif // __FUZZYMEMBERSHIP_H__