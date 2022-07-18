#include <fuzzyControl.hpp>

void fuzzyControl::initializer(const std::vector<fuzzyInput> &inputs, const std::vector<fuzzyOutput> &outputs, const std::vector<fuzzyRule> &rules) {
    __inputs = inputs;
    __outputs = outputs;
    __rules = rules; 
}

std::map<std::string, float>  fuzzyControl::updateInputs(std::map<std::string, int> &inputs_to_update) {
    std::map<std::__cxx11::string, float> ret;

    for ( auto input_to_update : inputs_to_update) {
        for ( auto &input : __inputs) {
            if (input.getName() == input_to_update.first) {
                input.setInput(input_to_update.second);
            }
        }
    }
    for ( auto &input : __inputs ) {
        input.fuzzyfication();
        //DEBUG_PRINT(("input %s %f %f %f\n", input.getName().c_str(), input.getMemberships()[0].getValue(), input.getMemberships()[1].getValue(),
        //input.getMemberships()[2].getValue()));
    }
    for ( auto &rule : __rules ) {
        rule.evaluate(__inputs, __outputs);
    }
    for ( auto &output : __outputs ) {
        //DEBUG_PRINT(("output %s %f %f %f\n", output.getName().c_str(), output.getMemberships()[0].getValue(), output.getMemberships()[1].getValue(),
        //output.getMemberships()[2].getValue()));
        output.defuzzification();
        ret.insert(std::pair<std::string,float> (output.getName(), output.getValue()));

        /* Clean membership outputs */
        for ( auto &mb : output.getMemberships()) {
            mb.setValue(0.0);
        }
    }
    return  ret;
}