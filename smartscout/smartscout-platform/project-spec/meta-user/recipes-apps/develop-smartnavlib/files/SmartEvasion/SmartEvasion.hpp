#ifndef CAB8CCC3_5624_4CEA_8519_DB44815628F0
#define CAB8CCC3_5624_4CEA_8519_DB44815628F0

#include <atomic>
#include <fstream>
#include <thread>
#include <utility>

#include <CartesionPosition.hpp>
#include <FuzzyControlSystem.hpp>
#include <FrameProcessor.hpp>
#include <Obstacle.hpp>
#include <PolarPosition.hpp>
#include <PositionEstimator.hpp>

class SmartEvasion {
public:
  /**
   * @brief Get the Instance of the SmartEvasion
   * 
   * @return SmartEvasion* 
   */
  static SmartEvasion* getInstance();
  /**
   * @brief Deleting copy constructor 
   * 
   */
  SmartEvasion(const SmartEvasion& obj) = delete;
  /**
   * @brief Singleton should not be assignable
   * 
   */
  void operator=(const SmartEvasion&) = delete;
  /**
   * @brief Play the smart evasion 
   * 
   * @param playSmartEvasion 
   */
  void playSmartEvasion(bool playSmartEvasion) { __play_smart_evasion.store(playSmartEvasion); }
  
private:
  /** Singleton instance */
  static SmartEvasion* __instance;
  /** Thread */
  std::thread __evasion_thread;
  /** Thread status */
  std::atomic<bool> __is_running;
  /** Play the SmartEvasion */
  std::atomic<bool> __play_smart_evasion;
  /** Recognized obstacles */
  std::vector<Obstacle> __obstacles;
  /** JSON file which describes the fuzzy system */
  static constexpr auto __FUZZY_S1_JSON{"/usr/bin/SmartEvasion-stage-1.json"};
  static constexpr auto __FUZZY_S2_JSON{"/usr/bin/SmartEvasion-stage-2.json"};
  /** Fuzzy control system object: STAGE 1 */
  std::shared_ptr<FuzzyControlSystem> __fuzzy_system_stage_1;
  /** Fuzzy control system object: STAGE 2 */
  std::shared_ptr<FuzzyControlSystem> __fuzzy_system_stage_2;
  /** Evasion constructor */
  SmartEvasion();
  /** Evasion destructor */
  ~SmartEvasion() = default;
  /**
   * @brief Wait a new target
   * 
   */
  void __waitNewTarget(); 
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
   * @brief Smart evasion
   * 
   * @param curr_position 
   * @param curr_robot_angle 
   * @param obstacles 
   * @return std::pair<float, float> 
   */
  std::pair<float, float> __evade(CartesianPosition curr_position, float curr_robot_angle, std::vector<Obstacle> obstacles);
  /**
   * @brief Wait for the image processing module to recognize and 
   * create the obstacle object
   * 
   * @param recognized_objects 
   * @param curr_robot_angle 
   * @param distance_to_obstacle 
   * @param curr_position 
   */
  void __obstacleDimensionExtractor(std::vector<RecognitionResult> recognized_objects, 
      float curr_robot_angle, float distance_to_obstacle, CartesianPosition curr_position);
  /**
   * @brief Add the angles
   * 
   * @param angle1
   * @param angle2 
   * @return float 
   */
  float __addAngles(float angle1, float angle2) {
    int ret = static_cast<int>(angle1 + angle2); 
    ret = ret % 360;
    if (ret > 180)
      ret -= 360;
    else if (ret < -180) 
      ret += 360;
    return static_cast<float>(ret); 
  }
  /**
   * @brief Subtract the angles
   * 
   * @param angle1
   * @param angle2 
   * @return float 
   */
  float __subtractAngles(float angle1, float angle2) {
    int ret = static_cast<int>(angle1 - angle2); 
    ret = ret % 360;
    if (ret > 180)
      ret -= 360;
    else if (ret < -180) 
      ret += 360;
    return static_cast<float>(ret); 
  }
  /**
   * @brief Get the supplementary angle
   * 
   * @return CartesianPosition 
   */
  CartesianPosition __supplementary(CartesianPosition point) {
    point.x = -point.x;
    point.y = -point.y;
    return point; 
  }
  /**
   * @brief Perform a multiplication between scalar and vector
   * 
   * @return float 
   */
  CartesianPosition __scalarVectorMult(CartesianPosition vector, float scalar) {
    CartesianPosition ret;
    ret.x = scalar * vector.x;
    ret.y = scalar * vector.y;
    return ret;
  }


};



#endif /* CAB8CCC3_5624_4CEA_8519_DB44815628F0 */
