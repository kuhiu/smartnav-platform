#include "FuzzyControlSystem.hpp"

//#define DEBUG_FUZZYCONTROLSYSTEM 1
#ifdef DEBUG_FUZZYCONTROLSYSTEM
 	#define DEBUG_PRINT(fmt, args...) printf( "DEBUG: %s:%d:%s(): " fmt, \
																						__FILE__, __LINE__, __func__, ##args)
#else
	#define DEBUG_PRINT(fmt, args...) /* Don't do anything in release builds */
#endif

constexpr const char *FuzzyControlSystem::__FUZZY_SYSTEM_KEY;
constexpr const char *FuzzyControlSystem::__INPUTS_KEY;
constexpr const char *FuzzyControlSystem::__OUTPUTS_KEY;
constexpr const char *FuzzyControlSystem::__RULES_KEY;

FuzzyControlSystem FuzzyControlSystem::parse(const nlohmann::json& fuzzy_control_system_json) {
  std::ostringstream err;
	std::vector<FuzzyInput> system_inputs;
	std::vector<FuzzyOutput> system_outputs;
	std::vector<FuzzyRule> system_rules; 
  
  // Check if it contains the fuzzy system
  if(!fuzzy_control_system_json.contains(__FUZZY_SYSTEM_KEY)) {
    err << "Invalid fuzzy_system arguments: " << fuzzy_control_system_json.dump();
    throw std::runtime_error(err.str());
  }
  // Check if it contains the input key
  if(!fuzzy_control_system_json.at(__FUZZY_SYSTEM_KEY).contains(__INPUTS_KEY)) {
    err << "No input key in " << fuzzy_control_system_json.at(__FUZZY_SYSTEM_KEY).dump();
    throw std::runtime_error(err.str());
  }
  // Check if it contains the output key
  if(!fuzzy_control_system_json.at(__FUZZY_SYSTEM_KEY).contains(__OUTPUTS_KEY)) {
    err << "No output key in " << fuzzy_control_system_json.at(__FUZZY_SYSTEM_KEY).dump();
    throw std::runtime_error(err.str());
  }
  // Check if it contains the rule key
  if(!fuzzy_control_system_json.at(__FUZZY_SYSTEM_KEY).contains(__RULES_KEY)) {
    err << "No rule key in " << fuzzy_control_system_json.at(__FUZZY_SYSTEM_KEY).dump();
    throw std::runtime_error(err.str());
  }
  // Check if inputs are a vector
  if(!fuzzy_control_system_json.at(__FUZZY_SYSTEM_KEY).at(__INPUTS_KEY).is_array()) {
    err << "Invalid inputs of fuzzy_system: " << fuzzy_control_system_json.at(__INPUTS_KEY).dump();
    throw std::runtime_error(err.str());
  }
  // Check if outputs are a vector
  if(!fuzzy_control_system_json.at(__FUZZY_SYSTEM_KEY).at(__OUTPUTS_KEY).is_array()) {
    err << "Invalid outputs of fuzzy_system: " << fuzzy_control_system_json.at(__OUTPUTS_KEY).dump();
    throw std::runtime_error(err.str());
  }
  // Check if rules are a vector
  if(!fuzzy_control_system_json.at(__FUZZY_SYSTEM_KEY).at(__RULES_KEY).is_array()) {
    err << "Invalid rules of fuzzy_system: " << fuzzy_control_system_json.at(__RULES_KEY).dump();
    throw std::runtime_error(err.str());
  }
  // Parse inputs
  for (const auto &input : fuzzy_control_system_json.at(__FUZZY_SYSTEM_KEY).at(__INPUTS_KEY)) {
    try {
      FuzzyInput fuzzy_input = FuzzyInput::parse(input);
      system_inputs.push_back(fuzzy_input);
    }
    catch(const std::exception& e) {
      err << "Error parsing as FuzzyInput: " << input.dump() << " WHAT: " << e.what();
      throw std::runtime_error(err.str());
    }
  }
  // Parse outputs
  for (const auto &output : fuzzy_control_system_json.at(__FUZZY_SYSTEM_KEY).at(__OUTPUTS_KEY)) {
    try {
      FuzzyOutput fuzzy_output = FuzzyOutput::parse(output);
      system_outputs.push_back(fuzzy_output);
    }
    catch(const std::exception& e) {
      err << "Error parsing as FuzzyOutput: " << output.dump() << " WHAT: " << e.what();
      throw std::runtime_error(err.str());
    }
  }
  // Parse rules
  for (const auto &rule : fuzzy_control_system_json.at(__FUZZY_SYSTEM_KEY).at(__RULES_KEY)) {
    try {
      FuzzyRule fuzzy_rule = FuzzyRule::parse(rule);
      system_rules.push_back(fuzzy_rule);
    }
    catch(const std::exception& e) {
      err << "Error parsing as FuzzyRule: " << rule.dump() << " WHAT: " << e.what();
      throw std::runtime_error(err.str());
    }
  }
  return FuzzyControlSystem(system_inputs, system_outputs, system_rules);   
}

std::vector<FuzzyOutput> FuzzyControlSystem::evaluate(std::vector<std::pair<std::string, float>> inputs_to_update) {
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