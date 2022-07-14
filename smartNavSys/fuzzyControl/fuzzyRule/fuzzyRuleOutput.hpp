#ifndef __FUZZYRULEOUTPUT_H__
#define __FUZZYRULEOUTPUT_H__

#include <string>
#include <vector>

#include <fuzzyElement.hpp>
#include <fuzzyOutput.hpp>

class fuzzyRuleOutput {
public:
    fuzzyRuleOutput(const std::vector<fuzzyElement> elements);
    ~fuzzyRuleOutput() = default;

    std::vector<fuzzyElement> getElements(void) const;
private:
    std::vector<fuzzyElement> __elements;
};

#endif // __FUZZYRULEOUTPUT_H__