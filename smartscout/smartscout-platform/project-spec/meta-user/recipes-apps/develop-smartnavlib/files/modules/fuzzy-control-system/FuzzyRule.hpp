/* 
  Rule type:

  IF INPUT1=HIGH AND/OR INPUT2=LOW THEN OUT1=LOW

  Where: 
  * "INPUT1=HIGH" is a condition of this rule.
  * "INPUT1=HIGH AND/OR INPUT2=LOW" is a condition of this rule, too.
  * "OUT1=LOW" is a condition of this rule, too.
  * "INPUTx" = Is one input.
  * "HIGH" = Is a fuzzy value of the this input.
*/

#ifndef F553A91F_E257_4635_80E9_4552D015C7A8
#define F553A91F_E257_4635_80E9_4552D015C7A8

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include <FuzzyAnd.hpp>
#include <FuzzyComparation.hpp>
#include <FuzzyCondition.hpp>
#include "FuzzyInput.hpp"
#include "FuzzyOutput.hpp"

#include <nlohmann/json.hpp>

using namespace nlohmann;

class FuzzyRule {  
public:
  /** FuzzyRule constructor */
  FuzzyRule(std::string name, 
            FuzzyCondition::FuzzyConditionPtr fuzzy_input_condition, 
            FuzzyCondition::FuzzyConditionPtr fuzzy_output_condition)
    : __name(name), 
      __fuzzy_input_condition(fuzzy_input_condition),
      __fuzzy_output_condition(fuzzy_output_condition) {};
  /** FuzzyRule destructor*/
  ~FuzzyRule() = default;
  /**
   * @brief Evaluate the inputs and update the outputs 
   * 
   * @param system_input 
   * @param system_output 
   */
  void evaluate(std::vector<FuzzyInput> &system_input, std::vector<FuzzyOutput> &system_output);
  /**
   * @brief Try to parse rule
   * 
   * @param rule_json Rule to parse
   * @return FuzzyRule 
   */
  static FuzzyRule parse(const nlohmann::json& rule_json);

private:
  /** Name key */
  static constexpr auto __NAME_KEY{"name"};
  /** Input condition key */
  static constexpr auto __INPUT_COND_KEY{"input_conditions"};
  /** Output condition key */
  static constexpr auto __OUTPUT_COND_KEY{"output_conditions"};
  /** Rule name */
  std::string __name;
  /** Fuzzy input condition */
  FuzzyCondition::FuzzyConditionPtr __fuzzy_input_condition;
  /** Fuzzy output condition */
  FuzzyCondition::FuzzyConditionPtr __fuzzy_output_condition;

};

#endif /* F553A91F_E257_4635_80E9_4552D015C7A8 */
