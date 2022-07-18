#ifndef __FUZZYELEMENT_H__
#define __FUZZYELEMENT_H__

#include <vector>

#include <fuzzyMembership.hpp>

class fuzzyElement {
public:
    fuzzyElement() = default;
    ~fuzzyElement() = default;

    void initializer(const std::string &__ioName, const std::string &membershipName);
    bool checkName(const std::string &name) const;
    bool checkMembershipName(const std::string &membership) const;
private: 
    std::string __ioName;
    std::string __membershipName;                   
};

#endif // __FUZZYELEMENT_H__