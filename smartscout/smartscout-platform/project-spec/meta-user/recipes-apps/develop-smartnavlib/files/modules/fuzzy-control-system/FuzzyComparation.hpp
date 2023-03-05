#ifndef B0988BAA_981F_4A9D_834D_83E81B0A29A7
#define B0988BAA_981F_4A9D_834D_83E81B0A29A7

#include <math.h>

#include <stdexcept>
#include <string>
#include <vector>

#include "FuzzyCondition.hpp"
#include "FuzzyInput.hpp"
#include "FuzzyOutput.hpp"

#include <nlohmann/json.hpp>

class FuzzyComparation : public FuzzyCondition {
public:
  /** FuzzyComparation constructor */
  FuzzyComparation(std::pair<std::string, std::string> comparation) 
    : __comparation(comparation) {};
  /** FuzzyComparation destructor */
  virtual ~FuzzyComparation() = default;
  /**
   * @brief Evaluate and condition
   * 
   * @param system_io 
   * @return float 
   */
  virtual float evaluate(std::vector<FuzzyInput> &system_input) const override;
  /**
   * @brief Update system outputs with value
   * 
   * @param value 
   */
  virtual void update(float value, std::vector<FuzzyOutput> &system_output) override;
  /**
   * @brief Try to parse comparation
   * 
   * @param comparation_json 
   * @return FuzzyConditionPtr 
   */
  static FuzzyConditionPtr parse(const nlohmann::json& comparation_json);

private:
  /** IO key */
  static constexpr auto __IO_KEY{"io"};
  /** Fuzzy value key */
  static constexpr auto __FUZZY_VALUE_KEY{"fuzzy_value"};
  /** Comparation */
  std::pair<std::string, std::string> __comparation;

};

#endif /* B0988BAA_981F_4A9D_834D_83E81B0A29A7 */
