#include <fuzzyRuleOutput.hpp>

fuzzyRuleOutput::fuzzyRuleOutput(const std::vector<fuzzyElement> elements) : __elements(elements) {}

std::vector<fuzzyElement> fuzzyRuleOutput::getElements(void) const {
    return __elements;
}