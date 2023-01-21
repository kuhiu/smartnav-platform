#include <FuzzyMembershipTrapezoidal.hpp>

#include <cmath>
#include <cstdlib>
#include <sstream>

constexpr const char *FuzzyMembershipTrapezoidal::__MB_TRAPEZOIDAL_KEY;
constexpr const char *FuzzyMembershipTrapezoidal::__MB_X1_KEY;
constexpr const char *FuzzyMembershipTrapezoidal::__MB_X2_KEY;
constexpr const char *FuzzyMembershipTrapezoidal::__MB_RIGHT_SLOPE_KEY;
constexpr const char *FuzzyMembershipTrapezoidal::__MB_LEFT_SLOPE_KEY;

float FuzzyMembershipTrapezoidal::compute_area_of_membership() {
  // area = height*(base+top)/2
  float base = __trapezoidal_points.x2 - __trapezoidal_points.x1; // a
  float dx1 = __fuzzy_value / __trapezoidal_points.left_slope;	// Ax = Ay * slope
  float dx2 = __fuzzy_value / __trapezoidal_points.right_slope;
  float top = base-dx1-dx2;	// b 
  return (abs(__fuzzy_value*(base + top)/2));
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

  if(!memb_function_json.contains(__NAME_KEY)) {
    err << "Trapezoidal object not contains the name key: " << memb_function_json.dump();
    throw std::runtime_error(err.str());
  }
  if(!memb_function_json.contains(__MB_TRAPEZOIDAL_KEY)) {
    err << "Trapezoidal object not contains the trapezoidal key: " << memb_function_json.dump();
    throw std::runtime_error(err.str());
  }
  if(!memb_function_json.at(__MB_TRAPEZOIDAL_KEY).is_array()) {
    err << "Trapezoidal object is not an array object: " << memb_function_json.at(__MB_TRAPEZOIDAL_KEY).dump();
    throw std::runtime_error(err.str());
  }
  // Parse trapezoidal points 
  for (const auto &point : memb_function_json.at(__MB_TRAPEZOIDAL_KEY)) {
    if(point.contains(__MB_X1_KEY)) 
      trapezoidal_points.x1 = point.at(__MB_X1_KEY);
    else if (point.contains(__MB_X2_KEY))
      trapezoidal_points.x2 = point.at(__MB_X2_KEY);
    else if (point.contains(__MB_RIGHT_SLOPE_KEY))
      trapezoidal_points.left_slope = point.at(__MB_RIGHT_SLOPE_KEY);
    else if (point.contains(__MB_LEFT_SLOPE_KEY))
      trapezoidal_points.right_slope = point.at(__MB_LEFT_SLOPE_KEY);
    else {
      err << "Trapezoidal object not contains " << __MB_X1_KEY << " " << " " <<
      __MB_X2_KEY << " " << __MB_RIGHT_SLOPE_KEY << " " << __MB_LEFT_SLOPE_KEY << 
      " keys: " << point.dump();
      throw std::runtime_error(err.str());
    }
  }

  return (FuzzyMembershipPtr(std::make_shared<FuzzyMembershipTrapezoidal>(memb_function_json.at(__NAME_KEY), trapezoidal_points)));
}