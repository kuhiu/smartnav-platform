#include <fuzzyElement.hpp>

void fuzzyElement::initializer(const std::string &ioName, const std::string &membershipName) {
    __ioName = ioName;
    __membershipName = membershipName;
}

bool fuzzyElement::checkName(const std::string &name) const {
    return (__ioName == name);
}

bool fuzzyElement::checkMembershipName(const std::string &membership) const {
    return (__membershipName == membership);
}