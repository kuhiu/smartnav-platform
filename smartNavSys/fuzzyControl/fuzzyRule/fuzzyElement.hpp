#ifndef __FUZZYELEMENT_H__
#define __FUZZYELEMENT_H__

#include <vector>

#include <fuzzyMembership.hpp>

class fuzzyElement {
public:
    fuzzyElement(const std::string &__ioName, const std::string &membershipName);
    ~fuzzyElement() = default;

    bool checkName(const std::string &name) const;
    bool checkMembershipName(const std::string &membership) const;
private: 
    const std::string __ioName;
    const std::string __membershipName;                   
};

#endif // __FUZZYELEMENT_H__