#ifndef __FUZZYRULEINPUT_H__
#define __FUZZYRULEINPUT_H__

#include <string>
#include <vector>

#include <fuzzyElement.hpp>
#include <fuzzyInput.hpp>

class fuzzyRuleInput {
public:
    fuzzyRuleInput() = default;
    ~fuzzyRuleInput() = default;
    
    void initializer(const std::vector<fuzzyElement> &elements);
    const std::vector<fuzzyElement> &getElements(void) const;
private:
    std::vector<fuzzyElement> __elements;
};

#endif // __FUZZYRULEINPUT_H__