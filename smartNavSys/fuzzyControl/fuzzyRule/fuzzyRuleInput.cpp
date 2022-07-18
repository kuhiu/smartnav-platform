#include <fuzzyRuleInput.hpp>

void fuzzyRuleInput::initializer(const std::vector<fuzzyElement> &elements) {
    __elements = elements;
};

const std::vector<fuzzyElement> &fuzzyRuleInput::getElements(void) const {
    return __elements;
}