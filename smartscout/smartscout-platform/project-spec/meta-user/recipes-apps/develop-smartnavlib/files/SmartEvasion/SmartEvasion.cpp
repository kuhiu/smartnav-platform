#include <SmartEvasion.hpp>

constexpr const char *SmartEvasion::__FUZZY_S1_JSON;
constexpr const char *SmartEvasion::__FUZZY_S2_JSON;

#define DEBUG_SMARTEVASION 1
#if defined(DEBUG_SMARTEVASION) 
 	#define DEBUG_PRINT(fmt, args...) printf( "DEBUG: %s:%d:%s(): " fmt, \
																						__FILE__, __LINE__, __func__, ##args)
#else
	#define DEBUG_PRINT(fmt, args...) /* Don't do anything in release builds */
#endif

SmartEvasion::SmartEvasion() {
  // Parse fuzzy system file 
  std::ifstream fuzzy_system_s1_file(__FUZZY_S1_JSON);
  const json fuzzy_system_s1_json = json::parse(fuzzy_system_s1_file);
  std::ifstream fuzzy_system_s2_file(__FUZZY_S2_JSON);
  const json fuzzy_system_s2_json = json::parse(fuzzy_system_s2_file);
  // Create fuzzy control system object
  __fuzzy_system_stage_1 = std::make_shared<FuzzyControlSystem>(FuzzyControlSystem::parse(fuzzy_system_s1_json));
  __fuzzy_system_stage_2 = std::make_shared<FuzzyControlSystem>(FuzzyControlSystem::parse(fuzzy_system_s2_json));
};

std::pair<float, float> SmartEvasion::evade(CartesianPosition curr_position, CartesianPosition rel_target_from_curr_pos,
      float curr_angle_to_target, float curr_robot_angle, std::vector<Obstacle> obstacles) {
  float w = 0;
  float alpha = 0;
  float theta = 0;
  float angle_correction;
  float current_destination_angle;
  PolarPosition rel_target_from_curr_pos_pol;
  PolarPosition closest_obstacle_point;
  PolarPosition furthest_obstacle_point;
  std::pair<float, float> ret; 
  std::vector<std::pair<std::string, float>> inputs;
  std::vector<FuzzyOutput> outputs;

  // If there are not obstacles
  if (!obstacles.empty()) {
    closest_obstacle_point = __getClosestObstaclePoint(curr_position, obstacles[0]);
    furthest_obstacle_point = __getFurthestObstaclePoint(curr_position, obstacles[0]);
    rel_target_from_curr_pos_pol = PositionEstimator::cartensianToPolar(rel_target_from_curr_pos);
    alpha = (closest_obstacle_point.distance / rel_target_from_curr_pos_pol.distance);
    theta = __getDifference(furthest_obstacle_point.angle, rel_target_from_curr_pos_pol.angle);
    DEBUG_PRINT("alpha %f, theta %f.\n", alpha, theta);
    // Fuzzy control system: Stage 1 
    inputs = {  {"alpha", alpha},
                {"theta", std::abs(theta)} };
    // Evaluate fuzzy system
    outputs = __fuzzy_system_stage_1->evaluate(inputs);
    // Read outputs 
    for (FuzzyOutput &output : outputs) {
      if (output.getName() == "w") 
        w = output.defuzzification();
    }  
    // Im looking go against the obstacle so..
    furthest_obstacle_point.angle = (furthest_obstacle_point.angle + 180.0);
    if (furthest_obstacle_point.angle > 180)
      furthest_obstacle_point.angle = furthest_obstacle_point.angle - 360; 
    DEBUG_PRINT("obstacle_angle %f.\n", furthest_obstacle_point.angle);
    current_destination_angle = w * furthest_obstacle_point.angle + (1-w) * curr_angle_to_target;
  }
  else 
    current_destination_angle = curr_angle_to_target;
  angle_correction = __getDifference(current_destination_angle, curr_robot_angle);
  // Fuzzy control system: Stage 2 
  inputs = { {"where_have_to_go", angle_correction} };
  // Evaluate fuzzy system
  outputs = __fuzzy_system_stage_2->evaluate(inputs);
  // Read outputs 
  for (FuzzyOutput &output : outputs) {
    if (output.getName() == "pwm0") 
      ret.first = output.defuzzification();
    else if (output.getName() == "pwm1")
      ret.second = output.defuzzification();
  }
  return ret;
};

PolarPosition SmartEvasion::__getClosestObstaclePoint(CartesianPosition curr_position, Obstacle obstacle) {
  PolarPosition ret;
  PolarPosition polar;
  CartesianPosition cartesian;

  cartesian.x = obstacle.getLeftmostPoint().x - curr_position.x;
  cartesian.y = obstacle.getLeftmostPoint().y - curr_position.y;
  ret = PositionEstimator::cartensianToPolar(cartesian);
  
  cartesian.x = obstacle.getRightmostPoint().x - curr_position.x;
  cartesian.y = obstacle.getRightmostPoint().y - curr_position.y;
  polar = PositionEstimator::cartensianToPolar(cartesian);
  if (polar.distance < ret.distance)
    ret = polar;

  return ret;
};

PolarPosition SmartEvasion::__getFurthestObstaclePoint(CartesianPosition curr_position, Obstacle obstacle) {
  PolarPosition ret;
  PolarPosition polar;
  CartesianPosition cartesian;

  cartesian.x = obstacle.getLeftmostPoint().x - curr_position.x;
  cartesian.y = obstacle.getLeftmostPoint().y - curr_position.y;
  ret = PositionEstimator::cartensianToPolar(cartesian);
  
  cartesian.x = obstacle.getRightmostPoint().x - curr_position.x;
  cartesian.y = obstacle.getRightmostPoint().y - curr_position.y;
  polar = PositionEstimator::cartensianToPolar(cartesian);
  if (polar.distance > ret.distance)
    ret = polar;

  return ret;
};

float SmartEvasion::__getDifference(float b1, float b2) {
  float r = fmod(b2 - b1, 360.0);
  if (r < -180.0)
    r += 360.0;
  if (r >= 180.0)
    r -= 360.0;
  return r;
}