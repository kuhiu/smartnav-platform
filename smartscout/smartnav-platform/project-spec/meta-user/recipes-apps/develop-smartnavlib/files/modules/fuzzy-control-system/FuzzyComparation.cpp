#include <FuzzyComparation.hpp>

constexpr const char *FuzzyComparation::__IO_KEY;
constexpr const char *FuzzyComparation::__FUZZY_VALUE_KEY;

//#define DEBUG_COMPARATION
#ifdef DEBUG_COMPARATION
#define DEBUG_PRINT(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...) do {} while (0)
#endif

float FuzzyComparation::evaluate(std::vector<FuzzyInput> &system_input) const {
  bool input_found = false;
  bool mb_found = false;
  for (auto &input : system_input) {
    DEBUG_PRINT("Input name %s, comparation name %s.\n", input.getName().c_str(),
    __comparation.first.c_str());
    if(input.getName() == __comparation.first) {
      input_found = true;
      for (auto &membership : input.getMemberships()) {
        mb_found = false;
        DEBUG_PRINT("Mb name %s, comparation name %s.\n", membership->getName().c_str(),
        __comparation.second.c_str());
        if(membership->getName() == __comparation.second) {
          mb_found = true;
          return membership->getValue();
        }
      }
    }
  }
  if(input_found == false) {
    throw std::runtime_error("Input not found in fuzzy system.");
  }
  else if (mb_found == false) {
    throw std::runtime_error("Membership not found in fuzzy system.");
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

  printf("Parsing as comparation.\n");
  
  comparation.first = comparation_json.at(__IO_KEY);
  comparation.second = comparation_json.at(__FUZZY_VALUE_KEY);
  return (FuzzyConditionPtr(std::make_shared<FuzzyComparation>(comparation)));
}