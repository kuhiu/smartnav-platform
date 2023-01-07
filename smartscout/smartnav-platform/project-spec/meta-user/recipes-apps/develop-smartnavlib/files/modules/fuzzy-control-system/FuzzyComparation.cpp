#include <FuzzyComparation.hpp>

constexpr const char *FuzzyComparation::__IO_KEY;
constexpr const char *FuzzyComparation::__FUZZY_VALUE_KEY;

float FuzzyComparation::evaluate(std::vector<FuzzyInput> &system_input) const {
  bool input_found = false;
  for (auto &input : system_input) {
    if(input.getName() == __comparation.first) {
      input_found = true;
      for (auto &membership : input.getMemberships()) {
        if(membership->getName() == __comparation.second)
          return membership->getValue();
      }
    }
  }
  if(input_found == false) {
    throw std::runtime_error("Input not found in fuzzy system.");
  }
  return -1.0;
}

void FuzzyComparation::update(float value, std::vector<FuzzyOutput> &system_output) {
  for (auto &output : system_output) {
    if(output.getName() == __comparation.first) {
      for (auto &membership : output.getMemberships()) {
        if(membership->getName() == __comparation.second) 
          membership->setValue(fmax(value, membership->getValue()));
      }
    }
  }
} 

FuzzyCondition::FuzzyConditionPtr FuzzyComparation::parse(const nlohmann::json& comparation_json) {
  std::ostringstream err;
  std::pair<std::string, std::string> comparation;

  if(!comparation_json.contains(__IO_KEY)) {
    err << "Comparation condition not contain io object: " << comparation_json.dump();
    throw std::runtime_error(err.str());
  }
  if(!comparation_json.contains(__FUZZY_VALUE_KEY)) {
    err << "Comparation condition not contain fuzzy value object: " << comparation_json.dump();
    throw std::runtime_error(err.str());
  }
  if(!comparation_json.at(__IO_KEY).is_string()) {
    err << "Comparation: " << __IO_KEY << " not contain an string object: " << comparation_json.dump();
    throw std::runtime_error(err.str());
  }
  if(!comparation_json.at(__FUZZY_VALUE_KEY).is_string()) {
    err << "Comparation: " << __FUZZY_VALUE_KEY << " not contain an string object: " << comparation_json.dump();
    throw std::runtime_error(err.str());
  }
  comparation.first = comparation_json.at(__IO_KEY);
  comparation.second = comparation_json.at(__FUZZY_VALUE_KEY);
  return (FuzzyConditionPtr(std::make_shared<FuzzyComparation>(comparation)));
}