#ifndef F1EC95FA_2EBE_49E9_8BA2_752CE00097F9
#define F1EC95FA_2EBE_49E9_8BA2_752CE00097F9

#include <chrono>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <vector>

#include <CartesionPosition.hpp>
#include <Obstacle.hpp>
#include <RecognitionResult.hpp>

#include <nlohmann/json.hpp>
#include <opencv2/opencv.hpp>

class Tracker {
public:
  /** StepsTracker struct */
  struct StepsTracker {
    /** Timestamp */
    int __timestamp;
    /** Angle: Absolute angle to where the robot was looking */
    float __angle_history;
    /** Absolute historical position points */
    CartesianPosition __position_history;
    /** StepsTracker constructor */
    StepsTracker(int timestamp, float angle_history, 
      CartesianPosition position_history) 
        : __timestamp(timestamp), __angle_history(angle_history), 
          __position_history(position_history) {}
    /**
     * @brief Conver the StepsTracker to JSON
     * 
     * @return nlohmann::json 
     */
    nlohmann::json toJson() const {
      nlohmann::json ret;

      ret["timestamp"] = __timestamp;
      ret["angles"] = __angle_history;
      ret["position"] = __position_history.toJson();
      return ret;
    };

  };
  /**
   * @brief Get the Instance of the Tracker
   * 
   * @return Tracker* 
   */
  static Tracker* getInstance();
  /**
   * @brief Deleting copy constructor 
   * 
   */
  Tracker(const Tracker& obj) = delete;
  /**
   * @brief Singleton should not be assignable
   * 
   */
  void operator=(const Tracker&) = delete;
  /**
   * @brief Get the Map object
   * 
   * @return const cv::Mat& 
   */
  const cv::Mat& getMap() const { return *__map; };
  /**
   * @brief Update the Map 
   * 
   */
  void updateMap(StepsTracker step) {
    int angle = step.__angle_history;
    cv::Point position(
        static_cast<int>(step.__position_history.x + (320 / 2)),
        static_cast<int>(step.__position_history.y + (240 / 2))
    );
    cv::Point arrow(
        static_cast<int>(position.x + 3 * cos(M_PI * angle / 180)),
        static_cast<int>(position.y + 3 * sin(M_PI * angle / 180))
    );
    cv::Point arrival_point(
        static_cast<int>(getRelativeTargetPos(step.__position_history).x + position.x),
        static_cast<int>(getRelativeTargetPos(step.__position_history).y + position.y)
    );

    cv::circle(*__map, position, 0, cv::Scalar(255, 255, 255), 3);
    cv::arrowedLine(*__map, position, arrow, cv::Scalar(0, 255, 0), 1);
    cv::arrowedLine(*__map, position, arrival_point, cv::Scalar(255, 150, 255), 1);
  }
  /**
   * @brief Add a new target (thread safe)
   * 
   * @param target 
   */
  void addTarget(CartesianPosition target) { 
    std::lock_guard<std::mutex> lock(__tracker_guard);
    __targets.push_back(target); 
  };
  /**
   * @brief Delete the target
   * 
   */
  void deleteTarget() {
    __targets.pop_front(); 
  }
  /**
   * @brief Remove the target reached (thread safe)
   * 
   * @param curr_position 
   * @return true 
   * @return false 
   */
  bool targetReached(CartesianPosition curr_position) { 
    bool ret = __arrivation(curr_position);
    if (ret) {
      std::lock_guard<std::mutex> lock(__tracker_guard);
      __targets.pop_front(); 
    }
    return ret;
  };
  /**
   * @brief Add a new obstacle (thread safe)
   * 
   * @param obstacle 
   */
  void addObstacle(Obstacle obstacle) { 
    std::lock_guard<std::mutex> lock(__tracker_guard);
    __obstacles.push_back(obstacle); 
  };
  /**
   * @brief Add a new recognition object (thread safe)
   * 
   * @param object 
   */
  void addRecognizedObject(RecognitionResult object) { 
    std::lock_guard<std::mutex> lock(__tracker_guard);
    __recognized_objects.push_back(object); 
  };
  /**
   * @brief Add a new steps tracker (thread safe)
   * 
   * @param steps_tracker 
   */
  void addStepsTracker(StepsTracker steps_tracker) { 
    std::lock_guard<std::mutex> lock(__tracker_guard);
    __steps_trackers.push_back(steps_tracker); 
  };
  /**
   * @brief Check if there are targets to reach
   * 
   * @return true 
   * @return false 
   */
  bool isTargetsEmpty() const { return(__targets.empty()); };
  /**
   * @brief Convert Tracker object to JSON (thread safe)
   * 
   * @return nlohmann::json 
   */
  nlohmann::json toJson() {
    int i=0, j=0, k=0, l=0;
    nlohmann::json ret;

    std::lock_guard<std::mutex> lock(__tracker_guard);
    ret["origin"] = __origin.toJson();
    ret["targets"];
    for (const CartesianPosition &target : __targets) {
      std::string name = "target_n" + std::to_string(i);
      ret["targets"][name] = target.toJson();
      i++;
    }
    ret["obstacles"];
    for (const Obstacle &obstacle : __obstacles) {
      std::string name = "obstacle_n" + std::to_string(j);
      ret["obstacles"][name] = obstacle.toJson(j);
      j++;
    }
    ret["recognized_objects"];
    for (const auto &recog_object : __recognized_objects) {
      std::string name = "recognized_object_n" + std::to_string(k);
      ret["recognized_objects"][name] = recog_object.toJson();
      k++;
    }
    ret["steps_trackers"];
    for (const auto &steps_tracker : __steps_trackers) {
      std::string name = "steps_tracker_n" + std::to_string(l);
      ret["steps_tracker"][name] = steps_tracker.toJson();
      l++;
    }

    return ret;
  };
  /**
   * @brief Get the angle where i have to go to reach
   * my destination.
   * 
   * @param rel_target_from_curr_pos Relative target position to the current position 
   * @return float: Angle where i have to go. left [0:180], right [0:-180]
   */
  float whereHaveToGo(const CartesianPosition curr_position) {
    CartesianPosition rel_target_from_curr_pos = getRelativeTargetPos(curr_position);
    //ret.distance = std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));
    float angle = atan2(rel_target_from_curr_pos.y, rel_target_from_curr_pos.x) * 180.0 / M_PI;
    if (angle > 180.0)
      angle = angle - 360;
    return angle;
  };
  /**
   * @brief Get the current Target To Reach 
   * 
   * @return CartesianPosition 
   */
  CartesianPosition getTargetToReach() const { return( __targets.front()); };
  /**
   * @brief Get the distance to the target.
   * 
   * @param curr_position 
   * @return CartesianPosition : Relative target position to the current position
   */
  CartesianPosition getRelativeTargetPos (const CartesianPosition curr_position) {
    CartesianPosition ret;
    CartesianPosition target = getTargetToReach();
    ret.x = target.x - curr_position.x;
    ret.y = target.y - curr_position.y;
    return ret;
  };

private:  
  /** Singleton instance */
  static Tracker* __instance;
  /** Arrival area [cm] */
  float __ARRIVAL_AREA = 10.0;
  /** Tracker guard */
  std::mutex __tracker_guard;
  /** Absolute Origin point position */
  const CartesianPosition __origin;
  /** Absolute Targets positions */
  std::deque<CartesianPosition> __targets;
  /** Absolute Obstacles positions */
  std::vector<Obstacle> __obstacles;
  /** Recognized objects (CNN outputs) */
  std::vector<RecognitionResult> __recognized_objects;
  /** Steps trackers */
  std::vector<StepsTracker> __steps_trackers;
  /** Map */
  std::unique_ptr<cv::Mat> __map; 
  /** Tracker constructor */
  Tracker() : __origin(CartesianPosition(0.0, 0.0)) {
    __map = std::make_unique<cv::Mat>(320, 240, CV_8UC3, cv::Scalar(0, 0, 0));
  };
  /** Utilities destructor */
  ~Tracker() = default;
  /**
   * @brief Check if the destination is reached
   * 
   * @param curr_position 
   * @return true 
   * @return false 
   */
  bool __arrivation(const CartesianPosition curr_position) {
    bool ret;
    float dx = std::fabs(curr_position.x - getTargetToReach().x);
    float dy = std::fabs(curr_position.y - getTargetToReach().y);
    if (dx < __ARRIVAL_AREA && dy < __ARRIVAL_AREA)
      ret = true;
    else 
      ret = false;
    return ret;
  };

};

#endif /* F1EC95FA_2EBE_49E9_8BA2_752CE00097F9 */
