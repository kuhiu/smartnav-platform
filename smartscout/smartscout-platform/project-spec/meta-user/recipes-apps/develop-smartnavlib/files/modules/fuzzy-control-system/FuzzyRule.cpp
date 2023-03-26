#include <FuzzyRule.hpp>

#include <sstream>

constexpr const char *FuzzyRule::__NAME_KEY;
constexpr const char *FuzzyRule::__INPUT_COND_KEY;
constexpr const char *FuzzyRule::__OUTPUT_COND_KEY;

//#define DEBUG_RULE 1
#ifdef DEBUG_RULE
 	#define DEBUG_PRINT(fmt, args...) printf( "DEBUG: %s:%d:%s(): " fmt, \
																						__FILE__, __LINE__, __func__, ##args)
#else
	#define DEBUG_PRINT(fmt, args...) /* Don't do anything in release builds */
#endif
void FuzzyRule::evaluate(std::vector<FuzzyInput> &system_input, std::vector<FuzzyOutput> &system_output) { 
  float rule_strength = __fuzzy_input_condition->evaluate(system_input); 
  DEBUG_PRINT("Rule name %s Rule strenght = %f.\n", __name.c_str(), rule_strength);
  __fuzzy_output_condition->update(rule_strength, system_output);
}

FuzzyRule FuzzyRule::parse(const nlohmann::json& rule_json) {
  std::ostringstream err;
  FuzzyCondition::FuzzyConditionPtr fuzzy_input_condition;
  FuzzyCondition::FuzzyConditionPtr fuzzy_output_condition;

  if(!rule_json.contains(__NAME_KEY)) {
    err << "Rule not contain name object: " << rule_json.dump();
    throw std::runtime_error(err.str());
  }
  if(!rule_json.contains(__INPUT_COND_KEY)) {
    err << "Rule not contain input condition object: " << rule_json.dump();
    throw std::runtime_error(err.str());
  }
  if(!rule_json.contains(__OUTPUT_COND_KEY)) {
    err << "Rule not contain output condition object: " << rule_json.dump();
    throw std::runtime_error(err.str());
  }

  for (const auto &condition : rule_json.at(__INPUT_COND_KEY)) {
    try {
      // Try to parse input condition as and
      fuzzy_input_condition = FuzzyAnd::parse(condition);
    }
    catch(const std::exception& e) {
      // The input condition could not be parsed as and
      DEBUG_PRINT("Test rule: It could not be parsed as and: WHAT: %s.\n", e.what());
    }
    try {
      // Try to parse input condition as comparation
      fuzzy_input_condition = FuzzyComparation::parse(condition);
    }
    catch(const std::exception& e) {
      // The input condition could not be parsed as comparation
      DEBUG_PRINT("Test rule: It could not be parsed as comparation: WHAT: %s\n", e.what());
    }
    if (fuzzy_input_condition == nullptr) {
      err << "The input condition of the rule could not be parsed: " << rule_json.at(__INPUT_COND_KEY).dump();
      throw std::runtime_error(err.str());
    }
  }

  for (const auto &condition : rule_json.at(__OUTPUT_COND_KEY)) { 
    try {
      // Try to parse output condition as and
      fuzzy_output_condition = FuzzyAnd::parse(condition);
    }
    catch(const std::exception& e) {
      // The output condition could not be parsed as and
      DEBUG_PRINT("Test rule: It could not be parsed as and: WHAT: %s.\n", e.what());
    }
    try {
      // Try to parse output condition as comparation
      fuzzy_output_condition = FuzzyComparation::parse(condition);
    }
    catch(const std::exception& e) {
      // The input condition could not be parsed as and
      DEBUG_PRINT("Test rule: It could not be parsed as comparation: WHAT: %s\n", e.what());
    }
    if (fuzzy_output_condition == nullptr) {
      err << "The output condition could not be parsed: " << rule_json.at(__OUTPUT_COND_KEY).dump();
      throw std::runtime_error(err.str());
    }
  }

  return (FuzzyRule(rule_json.at(__NAME_KEY).dump(), fuzzy_input_condition, fuzzy_output_condition));
}