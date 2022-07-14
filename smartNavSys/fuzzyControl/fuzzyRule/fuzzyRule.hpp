#ifndef __FUZZYRULE_H__
#define __FUZZYRULE_H__

#include <fuzzyRuleInput.hpp>
#include <fuzzyRuleOutput.hpp>

#include <string>
#include <vector>

class fuzzyRule {
public:
    fuzzyRule(const std::string &name, fuzzyRuleInput &ruleInputs, fuzzyRuleOutput &ruleOutputs);
    ~fuzzyRule() = default;

    void evaluate(std::vector<fuzzyInput> &inputs, std::vector<fuzzyOutput> &outputs) const;

private:
    const std::string __name;
    fuzzyRuleInput __ruleInputs;
    fuzzyRuleOutput __ruleOutputs;
};


#endif // __FUZZYRULE_H__