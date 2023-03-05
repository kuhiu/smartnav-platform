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

class SmartNav {
public:
  /** Smartnav constructor */
  SmartNav(PositionEstimator::cartesianPosition where_we_go);
  /** Smartnav destructor */
  ~SmartNav();

private:
  /** JSON file which describes the fuzzy system */
  static constexpr auto __FUZZY_JSON{"/usr/bin/fuzzy_system_v4.json"};
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
  /** Fuzzy control system object */
  std::shared_ptr<FuzzyControlSystem> __fuzzy_system;
  /** Travel destination */
  PositionEstimator::cartesianPosition __arrival_point;
  /** Decay graph */
  //DecayGraph __decay_graph;
  /** History points */
  std::vector<PositionEstimator::cartesianPosition> __position_history;
  std::vector<PositionEstimator::cartesianPosition> __arrival_point_history;
  std::vector<Obstacle> __obstacles;
  std::vector<float> __angle_history;
  std::vector<int> __timestamp;
  /** Utilities */
  utilities __utilities;
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
   * @brief Check if the destination is reached
   * 
   * @param curr_position 
   * @return true 
   * @return false 
   */
  bool __arrivation(PositionEstimator::cartesianPosition curr_position) {
    bool ret;
    float dx = std::fabs(curr_position.x - __arrival_point.x);
    float dy = std::fabs(curr_position.y - __arrival_point.y);
    if (dx < __ARRIVAL_AREA && dy < __ARRIVAL_AREA)
      ret = true;
    else 
      ret = false;
    return ret;
  };
  /**
   * @brief Get the distance and the angle of the target.
   * 
   * @param curr_position 
   * @return PositionEstimator::cartesianPosition 
   */
  PositionEstimator::cartesianPosition __getDestination (PositionEstimator::cartesianPosition curr_position) {
    PositionEstimator::cartesianPosition ret;

    ret.x = __arrival_point.x - curr_position.x;
    ret.y = __arrival_point.y - curr_position.y;
    return ret;
  };
  /**
   * @brief Get the current obstacle position 
   * 
   * @param curr_position 
   * @return PositionEstimator::cartesianPosition 
   */
  PositionEstimator::cartesianPosition __getObstaclePosition(PositionEstimator::cartesianPosition curr_position) {
    PositionEstimator::cartesianPosition ret;

    ret.x = __obstacles[0].getPosition().x - curr_position.x;
    ret.y = __obstacles[0].getPosition().y - curr_position.y;
    return ret;
  };
  /**
   * @brief Get the angle where i have to go to reach
   * my destination.
   * 
   * @param destination 
   * @return float: Angle where i have to go. left [0:180], right [0:-180]
   */
  float whereHaveToGo(PositionEstimator::cartesianPosition destination) {
    //ret.distance = std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));
    float angle = atan2(destination.y, destination.x) * 180.0 / M_PI;
    if (angle > 180.0)
      angle = angle - 360;
    return angle;
  };
  /**
   * @brief Get the difference between two bearings
   * 
   * @param b1 
   * @param b2 
   * @return float 
   */
  float __getDifference(float b1, float b2) {
    float r = fmod(b2 - b1, 360.0);
    if (r < -180.0)
      r += 360.0;
    if (r >= 180.0)
      r -= 360.0;
  	return r;
  }

};

#endif /* DBCD007B_2AE4_4807_BE39_8D3ADAFADDB8 */

