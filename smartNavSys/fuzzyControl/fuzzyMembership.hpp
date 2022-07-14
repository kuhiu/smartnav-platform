#ifndef __FUZZYMEMBERSHIP_H__
#define __FUZZYMEMBERSHIP_H__

#include <string>

class fuzzyMembership {
public:
    fuzzyMembership(const std::string &name, float point1, float point2, 
    float slope1, float slope2);
    ~fuzzyMembership() = default;

    float getValue(void) const;
    void setValue(float value);
    float getPoint1(void) const;
    float getPoint2(void) const;
    float getSlope1(void) const;
    float getSlope2(void) const;
    const std::string &getName(void) const;
private:
  const std::string __name;       
  float __value;              
  const float __point1;             
  const float __point2;             
  const float __slope1;             
  const float __slope2;             
};

#endif // __FUZZYMEMBERSHIP_H__