#include <FuzzyInput.hpp>

#include <sstream>

constexpr const char *FuzzyInput::__MEMBERSHIPS_FUNCTIONS_KEY;
constexpr const char *FuzzyInput::__NAME_KEY;

void FuzzyInput::fuzzyfication(float input_value) {
  for ( auto &membership : __memberships )
    membership->compute_degree_of_membership(input_value);
};

FuzzyInput FuzzyInput::parse(const nlohmann::json& input_json) {
  std::ostringstream err;
  std::vector<std::shared_ptr<FuzzyMembership>> memberships;
  
  // Check if it contains the name of io
  if(!input_json.contains(__NAME_KEY)) {
    err << "Invalid input arguments: " << input_json.dump();
    throw std::runtime_error(err.str());
  }
  // Check if it contains the membership functions
  if(!input_json.contains(__MEMBERSHIPS_FUNCTIONS_KEY)) {
    err << "Invalid input arguments: " << input_json.dump();
    throw std::runtime_error(err.str());
  }
  // Check if name is a string
  if(!input_json.at(__NAME_KEY).is_string()) {
    err << "Invalid type of input name: " << input_json.at(__NAME_KEY).dump();
    throw std::runtime_error(err.str());
  }
  // Check if membership vector 
  if(!input_json.at(__MEMBERSHIPS_FUNCTIONS_KEY).is_array()) {
    err << "Invalid type of input membership function: " << input_json.at(__MEMBERSHIPS_FUNCTIONS_KEY).dump();
    throw std::runtime_error(err.str());
  }

  // Parse inputs
  for (const auto &membership : input_json.at(__MEMBERSHIPS_FUNCTIONS_KEY)) {
    try {
      // Membership type 
      if(membership.contains(FuzzyMembershipTrapezoidal::__MB_TRAPEZOIDAL_KEY)  ) {
        auto fuzzy_membership_trapezoidal = FuzzyMembershipTrapezoidal::parse(membership);
        memberships.push_back(fuzzy_membership_trapezoidal);
      }
    }
    catch(const std::exception& e) {
      err << "Error parsing as FuzzyInput: " << input_json.dump() << " WHAT: " << e.what();
      throw std::runtime_error(err.str());
    }
  }
  return (FuzzyInput(input_json.at(__NAME_KEY), memberships));
};