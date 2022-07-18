#include <fuzzyOutput.hpp>

void fuzzyOutput::initializer(const std::string &name, std::vector<fuzzyMembership> &memberships) {
    __name = name; 
    __memberships = memberships;
}

const std::string fuzzyOutput::getName(void) const {
    return __name;
}

std::vector<fuzzyMembership> &fuzzyOutput::getMemberships(void) {
    return __memberships;
}

float fuzzyOutput::getValue(void) const {
    return __output;
}

void fuzzyOutput::defuzzification(void) {
    float sum_of_products = 0;   
    float sum_of_areas = 0;     
    float area;
    float centroid;

    for( auto &mf : __memberships){
        area = __compute_area_of_trapezoid(mf);
        centroid = mf.getPoint1() + (mf.getPoint2() - mf.getPoint1())/2;
        sum_of_products += area * centroid;
        sum_of_areas += area;
    }
    __output = sum_of_products/sum_of_areas;  
}

float fuzzyOutput::__compute_area_of_trapezoid(fuzzyMembership &mf) {
    float run_1;
    float run_2;
    float base;
    float top;
    float area;
    // h*(a+b)/2
    base = mf.getPoint2() - mf.getPoint1(); // a
    run_1 = mf.getValue()/mf.getSlope1();   // Ax = Ay * pendiente
    run_2 = mf.getValue()/mf.getSlope2();   // Ax = Ay * pendiente
    top = base-run_1-run_2;         // b 
    area = mf.getValue()*(base + top)/2;
    return area;
}