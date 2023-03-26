#ifndef A75E67F7_9C3F_4370_A541_4B1DB5BD2F02
#define A75E67F7_9C3F_4370_A541_4B1DB5BD2F02

#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

#include <CaptureFrame.hpp>
#include <Driver.hpp>
#include <DistanceSensors.hpp>
#include <FuzzyControlSystem.hpp>
#include <Headlights.hpp>
#include <PositionEstimator.hpp>
#include <utilities.hpp>
#include <DecayGraph.hpp>
#include <FrameProcessor.hpp>
#include <Obstacle.hpp>
#include <CartesionPosition.hpp>
#include <PolarPosition.hpp>
#include <Buttons.hpp>
#include <SmartEvasion.hpp>
#include <SmartLights.hpp>
#include <Tracker.hpp>
#include <Reporter.hpp>

class SmartNav {
public:
  /** Smartnav constructor */
  SmartNav();
  /** Smartnav destructor */
  ~SmartNav();
  /**
   * @brief The thread is running 
   * 
   * @return true 
   * @return false 
   */
  bool isRunning() const { return __is_running; };
  /**
   * @brief Stop the robot
   * 
   */
  void stop() { __is_running = true; };
  /**
   * @brief Add a new target 
   * 
   * @param arrival_point 
   */
  void newTarget(CartesianPosition arrival_point) {
    __tracker->addTarget(__position_estimator.relativizePoint(arrival_point));
  };

private:
  /** Arrival area [cm] */
  float __ARRIVAL_AREA = 10.0;
  /** Thread status */
  bool __is_running;
  /** Thread navigation */
  std::thread __navigation_thread;
  /** Driver object  */
	Driver __driver;
  /** Capture frame object */
  std::shared_ptr<CaptureFrame> __capture_frame;
  /** Headlights object */
  Headlights __headlights;
	/** Distance sensor object */
	DistanceSensors __distance_sensor;
  /** Position estimator object */
  PositionEstimator __position_estimator;
  /** Tracker object */
  std::shared_ptr<Tracker> __tracker;
  /** Evasion object */
  SmartEvasion __evader;
  /** Recognized obstacles */
  std::vector<Obstacle> __obstacles;
  /** Utilities */
  utilities __utilities;
  /** Lights control */
  SmartLights __smart_lights;
  /** Reporter object */
  std::shared_ptr<Reporter> __reporter;
  /**
   * @brief Frame callback
   * 
   * @param img 
   * @param ctx 
   */
  static void __frame_callback(std::shared_ptr<VirtualImage> img, void* ctx);
  /**
   * @brief Navigate
   * 
   */
  void __navigation();
  /**
   * @brief Wait for the image processing module to recognize and 
   * create the obstacle object
   * 
   * @param curr_robot_angle 
   * @param distance_to_obstacle 
   * @param curr_position 
   */
  void __visualization(float curr_robot_angle, float distance_to_obstacle, CartesianPosition curr_position);
  /**
   * @brief Check if the destination is reached
   * 
   * @param curr_position 
   * @return true 
   * @return false 
   */
  bool __arrivation(CartesianPosition curr_position, CartesianPosition current_target_position) {
    bool ret;
    float dx = std::fabs(curr_position.x - current_target_position.x);
    float dy = std::fabs(curr_position.y - current_target_position.y);
    if (dx < __ARRIVAL_AREA && dy < __ARRIVAL_AREA)
      ret = true;
    else 
      ret = false;
    return ret;
  };
  /**
   * @brief Get the distance to the target.
   * 
   * @param curr_position 
   * @return CartesianPosition : Relative target position to the current position
   */
  CartesianPosition __getRelativeTargetPos (CartesianPosition curr_position, CartesianPosition current_target_position) {
    CartesianPosition ret;

    ret.x = current_target_position.x - curr_position.x;
    ret.y = current_target_position.y - curr_position.y;
    return ret;
  };
  /**
   * @brief Get the angle where i have to go to reach
   * my destination.
   * 
   * @param rel_target_from_curr_pos Relative target position to the current position 
   * @return float: Angle where i have to go. left [0:180], right [0:-180]
   */
  float __whereHaveToGo(CartesianPosition rel_target_from_curr_pos) {
    //ret.distance = std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));
    float angle = atan2(rel_target_from_curr_pos.y, rel_target_from_curr_pos.x) * 180.0 / M_PI;
    if (angle > 180.0)
      angle = angle - 360;
    return angle;
  };

};

#endif /* DBCD007B_2AE4_4807_BE39_8D3ADAFADDB8 */

