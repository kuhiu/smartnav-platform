#include <FuzzyAnd.hpp>

constexpr const char *FuzzyAnd::__AND_KEY;

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
  FuzzyConditionPtr comparation;
  std::vector<FuzzyConditionPtr> comparations;

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
      comparation = FuzzyAnd::parse(comparation_json);
    }
    catch(const std::exception& e) {
      // And comparation could not be parsed as and
    }
    try {
      comparation = FuzzyComparation::parse(comparation_json);
    }
    catch(const std::exception& e) {
      // And comparation could not be parsed as comparation
    }

    if(comparation == nullptr) {
      err << "And condition is not an array: " << and_json.dump();
      throw std::runtime_error(err.str());
    }
    else 
      comparations.push_back(comparation);
  }
  return (FuzzyConditionPtr(std::make_shared<FuzzyAnd>(comparations)));
};