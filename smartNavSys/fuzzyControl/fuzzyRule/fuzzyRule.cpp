#include <fuzzyRule.hpp>
#include <iostream>

void fuzzyRule::initializer(const std::string &name, fuzzyRuleInput &ruleInputs, fuzzyRuleOutput &ruleOutputs) {
    __name = name;
    __ruleInputs = ruleInputs;
    __ruleOutputs = ruleOutputs;
}

void fuzzyRule::evaluate(std::vector<fuzzyInput> &inputs, std::vector<fuzzyOutput> &outputs) const {
    float strength = UPPER_LIMIT;
    for ( auto &element : __ruleInputs.getElements() ) {     /* for each element of rule */
        for ( auto &input : inputs ) {       /* for each input of the fuzzy system */
            if (element.checkName(input.getName())) {   
                for ( auto &membership : input.getMemberships()) { /* for each membership function defined on input */
                    if (element.checkMembershipName(membership.getName())) {
                        /* The name of membership and input match with the rule */
                        strength = fmin(strength,membership.getValue());
                    }
                }
            }
        }
    }
    for ( auto &element : __ruleOutputs.getElements() ) {     /* for each element of rule */
        for ( auto &output : outputs ) {       /* for each input of the fuzzy system */
            if (element.checkName(output.getName())) {   
                for ( auto &membership : output.getMemberships()) { /* for each membership function defined on input */
                    if (element.checkMembershipName(membership.getName())) {
                        /* The name of membership and input match with the rule */
                        membership.setValue(fmax(strength,membership.getValue()));  
                    }
                }
            }
        }
    }   
}

