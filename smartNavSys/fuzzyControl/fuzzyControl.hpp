#ifndef __FUZZYCONTROL_H__
#define __FUZZYCONTROL_H__

#include <ioConfig.hpp>
#include <fuzzyInput.hpp>
#include <fuzzyOutput.hpp>
#include <fuzzyRule.hpp>
#include <common.hpp>

#include <map>
#include <set>

class fuzzyControl {
public:
    fuzzyControl(const std::vector<fuzzyInput> inputs, const std::vector<fuzzyOutput> outputs, const std::vector<fuzzyRule> rules);
    ~fuzzyControl() = default;
    
    std::map<std::string, float>  updateInputs(std::map<std::string, int> &inputs_to_update);
private:
    std::vector<fuzzyInput> __inputs; 
    std::vector<fuzzyOutput> __outputs; 
    const std::vector<fuzzyRule> __rules; 
};



#endif // __FUZZYCONTROL_H__