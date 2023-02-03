#ifndef AAF78FC2_7624_47D0_9F79_E2435CD45FBD
#define AAF78FC2_7624_47D0_9F79_E2435CD45FBD

#include <math.h>

#include <stdexcept>
#include <vector>

#include <nlohmann/json.hpp>

#include <FuzzyCondition.hpp>
#include <FuzzyComparation.hpp>

class FuzzyAnd : public FuzzyCondition {
public:
  /** FuzzyAnd constructor */
  FuzzyAnd(std::vector<FuzzyConditionPtr> condition) : __conditions(condition) {};
  /** FuzzyAnd destructor */
  virtual ~FuzzyAnd() = default;
  /**
   * @brief Evaluate and condition
   * 
   * @param system_io 
   * @return float 
   */
  virtual float evaluate(std::vector<FuzzyInput> &system_input) const override;
  /**
   * @brief Update and with a new value
   * 
   * @param value 
   * @param system_io 
   */
  virtual void update(float value, std::vector<FuzzyOutput> &system_output) override;
  /**
   * @brief Try to parse and condition
   * 
   * @param and_json 
   * @return FuzzyConditionPtr 
   */
  static FuzzyConditionPtr parse(const nlohmann::json& and_json);

private:
  /** And key */
  static constexpr auto __AND_KEY{"and"};
  /** Max evaluate result */
  const float __UPPER_LIMIT = 1.0;
  /** Fuzzy conditions */
  std::vector<FuzzyConditionPtr> __conditions;
  
};


#endif /* AAF78FC2_7624_47D0_9F79_E2435CD45FBD */
