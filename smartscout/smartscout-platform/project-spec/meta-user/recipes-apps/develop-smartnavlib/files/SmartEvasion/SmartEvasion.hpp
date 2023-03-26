#ifndef CAB8CCC3_5624_4CEA_8519_DB44815628F0
#define CAB8CCC3_5624_4CEA_8519_DB44815628F0

#include <fstream>
#include <utility>

#include <CartesionPosition.hpp>
#include <FuzzyControlSystem.hpp>
#include <Obstacle.hpp>
#include <PolarPosition.hpp>
#include <PositionEstimator.hpp>

class SmartEvasion {
public:
  /** Evasion constructor */
  SmartEvasion();
  /** Evasion destructor */
  ~SmartEvasion() = default;
  /**
   * @brief Smart evasion
   * 
   * @param curr_position 
   * @param curr_arrival_point 
   * @param brightness 
   * @param curr_angle_to_go 
   * @param curr_robot_angle 
   * @return std::pair<float, float> 
   */
  std::pair<float, float> evade(CartesianPosition curr_position, CartesianPosition curr_arrival_point, 
      float curr_angle_to_go, float curr_robot_angle, std::vector<Obstacle> obstacles);
  
private:
  /** JSON file which describes the fuzzy system */
  static constexpr auto __FUZZY_S1_JSON{"/usr/bin/SmartEvasion-stage-1.json"};
  static constexpr auto __FUZZY_S2_JSON{"/usr/bin/SmartEvasion-stage-2.json"};
  /** Fuzzy control system object: STAGE 1 */
  std::shared_ptr<FuzzyControlSystem> __fuzzy_system_stage_1;
  /** Fuzzy control system object: STAGE 2 */
  std::shared_ptr<FuzzyControlSystem> __fuzzy_system_stage_2;
  /**
   * @brief Get the closest obstacle point relative to the current position
   * 
   * @param curr_position 
   * @return PolarPosition 
   */
  PolarPosition __getClosestObstaclePoint(CartesianPosition curr_position, Obstacle obstacle);
  /**
   * @brief Get the furthes obstacle point relative to the current position
   * 
   * @param curr_position 
   * @return PolarPosition 
   */
  PolarPosition __getFurthestObstaclePoint(CartesianPosition curr_position, Obstacle obstacle);
  /**
   * @brief Get the difference between two bearings
   * 
   * @param b1 
   * @param b2 
   * @return float 
   */
  float __getDifference(float b1, float b2);

};



#endif /* CAB8CCC3_5624_4CEA_8519_DB44815628F0 */
