#include <FuzzyMembershipTrapezoidal.hpp>
#include <sstream>

constexpr const char *FuzzyMembershipTrapezoidal::__MB_TRAPEZOIDAL_KEY;
constexpr const char *FuzzyMembershipTrapezoidal::__MB_X1_KEY;
constexpr const char *FuzzyMembershipTrapezoidal::__MB_X2_KEY;
constexpr const char *FuzzyMembershipTrapezoidal::__MB_RIGHT_SLOPE_KEY;
constexpr const char *FuzzyMembershipTrapezoidal::__MB_LEFT_SLOPE_KEY;

float FuzzyMembershipTrapezoidal::compute_area_of_membership() {
  // area = height*(base+top)/2
  float base = __trapezoidal_points.x2 - __trapezoidal_points.x1; // a
  float dx1 = __fuzzy_value / __trapezoidal_points.right_slope;	// Ax = Ay * slope
  float dx2 = __fuzzy_value / __trapezoidal_points.left_slope;
  float top = base-dx1-dx2;	// b 
  return (__fuzzy_value*(base + top)/2);
}


float FuzzyMembershipTrapezoidal::compute_centroid_of_membership() { 
  return (__trapezoidal_points.x1 + ((__trapezoidal_points.x2 - __trapezoidal_points.x1)/2)); 
}

void FuzzyMembershipTrapezoidal::compute_degree_of_membership(float input_value) {
  float delta_1 = input_value - __trapezoidal_points.x1;
  float delta_2 = __trapezoidal_points.x2 - input_value;

  if ((delta_1 <= 0) || (delta_2 <= 0)) 
    // The input is out of the membership function
    __fuzzy_value = 0.0;                    
  else{
    __fuzzy_value = fmin(	(__trapezoidal_points.left_slope  * delta_1), 
                (__trapezoidal_points.right_slope * delta_2));
    __fuzzy_value = fmin( __fuzzy_value, __UPPER_LIMIT);       
  }
}

FuzzyMembership::FuzzyMembershipPtr FuzzyMembershipTrapezoidal::parse(const nlohmann::json& memb_function_json) {
  std::ostringstream err;
  TrapezoidalPoints trapezoidal_points;
  std::string name;
  if(!memb_function_json.is_array()) {
    err << "Trapezoidal object is not an array object: " << memb_function_json.dump();
    throw std::runtime_error(err.str());
  }

  name = memb_function_json.at(__NAME_KEY);
  trapezoidal_points.x1 = memb_function_json.at(__MB_X1_KEY);
  trapezoidal_points.x2 = memb_function_json.at(__MB_X2_KEY);
  trapezoidal_points.left_slope = memb_function_json.at(__MB_RIGHT_SLOPE_KEY);
  trapezoidal_points.right_slope = memb_function_json.at(__MB_LEFT_SLOPE_KEY);

  return (FuzzyMembershipPtr(std::make_shared<FuzzyMembershipTrapezoidal>(name, trapezoidal_points)));
}