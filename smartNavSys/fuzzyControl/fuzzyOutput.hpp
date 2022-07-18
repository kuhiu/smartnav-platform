#ifndef __FUZZYOUTPUT_H__
#define __FUZZYOUTPUT_H__

#include <string>
#include <vector>
#include <cmath>

#include <fuzzyElement.hpp>

class fuzzyOutput {
public:
    fuzzyOutput() = default;
    ~fuzzyOutput() = default;

    void initializer(const std::string &name, std::vector<fuzzyMembership> &memberships);
    void defuzzification(void);

    const std::string getName(void) const;
    std::vector<fuzzyMembership> &getMemberships(void);

    float getValue(void) const;
private:
    std::string __name;
    std::vector<fuzzyMembership> __memberships;
    mutable float __output;

    float __compute_area_of_trapezoid(fuzzyMembership &mf);
};

#endif // __FUZZYOUTPUT_H__