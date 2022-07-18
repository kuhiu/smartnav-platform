#include <fuzzyInput.hpp>

void fuzzyInput::initializer(const std::string &name, std::vector<fuzzyMembership> &memberships) {
    __name = name;
    __memberships = memberships;
}

void fuzzyInput::fuzzyfication(void) {
    for ( auto &membership : __memberships ){
        __compute_degree_of_membership(membership, __input);
    }
}

void fuzzyInput::__compute_degree_of_membership(fuzzyMembership &mf, int input) {
    float delta_1 = input - mf.getPoint1();
    float delta_2 = mf.getPoint2() - input;
    if ((delta_1 <= 0) || (delta_2 <= 0))   // La entrada esta fuera de la funcion de pertenencia 
        mf.setValue(0.0);                      // El grado de pertenencia es 0
    else{
        mf.setValue(fmin((mf.getSlope1()*delta_1), (mf.getSlope2()*delta_2)));
        mf.setValue(fmin( mf.getValue(), UPPER_LIMIT));       
    }
}

const std::string &fuzzyInput::getName(void) const {
    return __name;
}

std::vector<fuzzyMembership> &fuzzyInput::getMemberships(void) {
    return __memberships;
}

void fuzzyInput::setInput(int input) {
    __input = input;
}