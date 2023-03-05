#include <FuzzyAnd.hpp>

constexpr const char *FuzzyAnd::__AND_KEY;

//#define DEBUG_AND 1
#ifdef DEBUG_AND
 	#define DEBUG_PRINT(fmt, args...) printf( "DEBUG: %s:%d:%s(): " fmt, \
																						__FILE__, __LINE__, __func__, ##args)
#else
	#define DEBUG_PRINT(fmt, args...) /* Don't do anything in release builds */
#endif


float FuzzyAnd::evaluate(std::vector<FuzzyInput> &system_input) const {
  float strength = __UPPER_LIMIT;
  if(__conditions.empty())
    throw std::runtime_error("And condition is empty.");
  else if(__conditions.size() == 1)
    throw std::runtime_error("And condition has only one condition.");
  for(auto &condition : __conditions)
    strength = fmin(strength, condition->evaluate(system_input));
  return strength;
};

void FuzzyAnd::update(float value, std::vector<FuzzyOutput> &system_output) {
  if(__conditions.empty())
    throw std::runtime_error("And condition is empty.");
  else if(__conditions.size() == 1)
    throw std::runtime_error("And condition has only one input.");
  for(auto &condition : __conditions)
    condition->update(value, system_output);
};

FuzzyCondition::FuzzyConditionPtr FuzzyAnd::parse(const nlohmann::json& and_json) {
  std::ostringstream err;
  FuzzyConditionPtr condition;
  std::vector<FuzzyConditionPtr> conditions;

  if(!and_json.contains(__AND_KEY)) {
    err << "And condition not contain and object: " << and_json.dump();
    throw std::runtime_error(err.str());
  }
  if(!and_json.at(__AND_KEY).is_array()) {
    err << "And condition is not an array: " << and_json.dump();
    throw std::runtime_error(err.str());
  }

  for (auto &comparation_json : and_json.at(__AND_KEY)) {
    try {
      condition = FuzzyAnd::parse(comparation_json);
    }
    catch(const std::exception& e) {
      // And comparation could not be parsed as and
      DEBUG_PRINT("Test and: It could not be parsed as and.\n");
    }
    try {
      condition = FuzzyComparation::parse(comparation_json);
    }
    catch(const std::exception& e) {
      // And comparation could not be parsed as comparation
      DEBUG_PRINT("Test and: It could not be parsed as comparation.\n");
    }

    if(condition == nullptr) {
      err << "And condition is not an array: " << and_json.dump();
      throw std::runtime_error(err.str());
    }
    else 
      conditions.push_back(condition);
  }
  return (FuzzyConditionPtr(std::make_shared<FuzzyAnd>(conditions)));
};