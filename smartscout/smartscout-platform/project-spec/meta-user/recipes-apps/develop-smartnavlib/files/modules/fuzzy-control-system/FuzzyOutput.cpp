#include <FuzzyOutput.hpp>
#include <FuzzyMembershipTrapezoidal.hpp>

#include <sstream>

constexpr const char *FuzzyOutput::__MEMBERSHIPS_FUNCTIONS_KEY;
constexpr const char *FuzzyOutput::__NAME_KEY;

//#define DEBUG_OUTPUT 1
#ifdef DEBUG_OUTPUT
 	#define DEBUG_PRINT(fmt, args...) printf( "DEBUG: %s:%d:%s(): " fmt, \
																						__FILE__, __LINE__, __func__, ##args)
#else
	#define DEBUG_PRINT(fmt, args...) /* Don't do anything in release builds */
#endif

FuzzyOutput FuzzyOutput::parse(const nlohmann::json& output_json) {
  std::ostringstream err;
  std::vector<std::shared_ptr<FuzzyMembership>> memberships;

  // Check if it contains the name of io
  if(!output_json.contains(__NAME_KEY)) {
    err << "Invalid output arguments: " << output_json.dump();
    throw std::runtime_error(err.str());
  }
  // Check if it contains the membership functions
  if(!output_json.contains(__MEMBERSHIPS_FUNCTIONS_KEY)) {
    err << "Invalid output arguments: " << output_json.dump();
    throw std::runtime_error(err.str());
  }
  // Check if name is a string
  if(!output_json.at(__NAME_KEY).is_string()) {
    err << "Invalid type of output name: " << output_json.at(__NAME_KEY).dump();
    throw std::runtime_error(err.str());
  }
  // Check if membership vector 
  if(!output_json.at(__MEMBERSHIPS_FUNCTIONS_KEY).is_array()) {
    err << "Invalid type of output membership function: " << output_json.at(__MEMBERSHIPS_FUNCTIONS_KEY).dump();
    throw std::runtime_error(err.str());
  }
  // Parse inputs
  for (const auto &membership : output_json.at(__MEMBERSHIPS_FUNCTIONS_KEY)) {
    try {
      // Membership type 
      if(membership.contains(FuzzyMembershipTrapezoidal::__MB_TRAPEZOIDAL_KEY)  ) {
        auto fuzzy_membership_trapezoidal = FuzzyMembershipTrapezoidal::parse(membership);
        memberships.push_back(fuzzy_membership_trapezoidal);
      }
    }
    catch(const std::exception& e) {
      err << "Error parsing as FuzzyInput: " << output_json.dump() << "WHAT: " << e.what();;
      throw std::runtime_error(err.str());
    }
  }
  return (FuzzyOutput(output_json.at(__NAME_KEY), memberships));
};

float FuzzyOutput::defuzzification() {
  float area;
  float centroid;
  float sum_of_areas = 0;     
  float sum_of_products = 0;   

  for( auto &membership : __memberships){
    area = membership->compute_area_of_membership();
    centroid = membership->compute_centroid_of_membership();
    //DEBUG_PRINT("Centroid %f, area %f.\n", centroid, area);
    sum_of_products += area * centroid;
    sum_of_areas += area;
  }
  return (sum_of_products/sum_of_areas);  
}