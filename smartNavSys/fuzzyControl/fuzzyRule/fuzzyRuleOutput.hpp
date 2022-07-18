#ifndef __FUZZYRULEOUTPUT_H__
#define __FUZZYRULEOUTPUT_H__

#include <string>
#include <vector>

#include <fuzzyElement.hpp>
#include <fuzzyOutput.hpp>

class fuzzyRuleOutput {
public:
    fuzzyRuleOutput() = default;
    ~fuzzyRuleOutput() = default;

    void initializer(const std::vector<fuzzyElement> elements);
    std::vector<fuzzyElement> getElements(void) const;
private:
    std::vector<fuzzyElement> __elements;
};

#endif // __FUZZYRULEOUTPUT_H__