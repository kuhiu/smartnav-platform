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
	std::vector<FuzzyOutput> evaluate(std::vector<std::pair<std::string, float>> inputs_to_update);
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