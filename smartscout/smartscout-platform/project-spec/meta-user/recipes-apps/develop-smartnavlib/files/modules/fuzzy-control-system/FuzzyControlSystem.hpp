#ifndef __FUZZYCONTROLSYSTEM_H__
#define __FUZZYCONTROLSYSTEM_H__

#include <exception>
#include <nlohmann/json.hpp>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <utility>

#include "FuzzyRule.hpp"
#include "FuzzyInput.hpp"
#include "FuzzyOutput.hpp"

using namespace nlohmann;

#define DEBUG_SYSTEM 1
#ifdef DEBUG_SYSTEM
#define DEBUG_PRINT(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...) do {} while (0)
#endif

class FuzzyControlSystem {
public:
	/** FuzzyControlSystem constructor */
	FuzzyControlSystem(	std::vector<FuzzyInput> system_inputs,
											std::vector<FuzzyOutput> system_outputs,
											std::vector<FuzzyRule> system_rules ) : 
											__system_inputs(system_inputs),
											__system_outputs(system_outputs),
											__system_rules(system_rules) {};
	/** FuzzyControlSystem destructor */
	~FuzzyControlSystem() = default;
	/**
	 * @brief Update system input
	 * 
	 * @param inputs_to_update 
	 * @return std::vector<fuzzyOutput> Return fuzzy_outputs
	 */
<<<<<<< HEAD:smartscout/smartscout-platform/project-spec/meta-user/recipes-apps/develop-smartnavlib/files/modules/fuzzy-control-system/FuzzyControlSystem.hpp
	std::vector<FuzzyOutput> evaluate(std::vector<std::pair<std::string, float>> inputs_to_update);
=======
	std::vector<FuzzyOutput> evaluate(std::vector<std::pair<std::string, float>> inputs_to_update) {
		bool found = false;

		// Check input name 
		for (auto &system_input : __system_inputs) {
			found = false;
			for (auto &input_to_update : inputs_to_update) {
				DEBUG_PRINT("Inputs name: %s - %s.\n", system_input.getName().c_str(), input_to_update.first.c_str());
				if (system_input.getName() == input_to_update.first) {
					// Input fuzzification
					system_input.fuzzyfication(input_to_update.second);	
					found = true;
				}
			}
			if (found == false) {
				std::stringstream err;
				err << "Input not defined in the fuzzy system.";
				throw std::runtime_error(err.str().c_str());
			}
		}
		// Test
		for (auto &system_input : __system_inputs) {
			DEBUG_PRINT("Input name: %s.\n", system_input.getName().c_str());
			for (auto &system_membership : system_input.getMemberships()) {
				DEBUG_PRINT("Membership values: %f.\n", system_membership->getValue());
			}
		}

		// Before evaluate clean all membership functions of each output
		for (auto &system_output : __system_outputs)
			system_output.resetMembershipFuntions();

		// Rules evaluation
		for (auto &rule : __system_rules) 
			rule.evaluate(__system_inputs, __system_outputs);

		// Test
		for (auto &system_output : __system_outputs) {
			DEBUG_PRINT("Output name: %s.\n", system_output.getName().c_str());
			for (auto &system_membership : system_output.getMemberships()) {
				DEBUG_PRINT("Membership values: %f.\n", system_membership->getValue());
			}
		}

		// Output deffuzification
    for ( auto &output : __system_outputs ) {
			output.defuzzification();
    }

		return __system_outputs;
	}
>>>>>>> master:smartscout/smartnav-platform/project-spec/meta-user/recipes-apps/develop-smartnavlib/files/modules/fuzzy-control-system/FuzzyControlSystem.hpp
	/**
	 * @brief Try to parse system.json  
	 * 
	 * @param fuzzy_control_system_json 
	 * @return FuzzyControlSystem 
	 */
	static FuzzyControlSystem parse(const nlohmann::json& fuzzy_control_system_json);

private:
	/** Fuzzy system key */
	static constexpr auto __FUZZY_SYSTEM_KEY{"fuzzy_system"};
	/** Inputs key */
	static constexpr auto __INPUTS_KEY{"inputs"};
	/** Outputs key */
	static constexpr auto __OUTPUTS_KEY{"outputs"};
	/** Rule key */
	static constexpr auto __RULES_KEY{"rules"};
	/** System inputs */
	std::vector<FuzzyInput> __system_inputs;
	/** System outputs */
	std::vector<FuzzyOutput> __system_outputs;
	/** System rules */
	std::vector<FuzzyRule> __system_rules; 

};

#endif // __FUZZYCONTROLSYSTEM_H__