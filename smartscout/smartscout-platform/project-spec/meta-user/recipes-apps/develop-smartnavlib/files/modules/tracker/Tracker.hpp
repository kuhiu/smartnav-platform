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
    /** Historical target position: Relative to the currect position */
    CartesianPosition __rel_target_from_curr_pos;
    /** StepsTracker constructor */
    StepsTracker(int timestamp, float angle_history, 
      CartesianPosition position_history, CartesianPosition rel_target_from_curr_pos) 
        : __timestamp(timestamp), __angle_history(angle_history), 
          __position_history(position_history), __rel_target_from_curr_pos (rel_target_from_curr_pos) {}
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
      ret["arrival_point"] = __rel_target_from_curr_pos.toJson();
      return ret;
    };

  };
  /** Tracker constructor */
  Tracker() : __origin(CartesianPosition(0.0, 0.0)) {};
  /** Utilities destructor */
  ~Tracker() = default;
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
   * @brief Get the current Target To Reach 
   * 
   * @return CartesianPosition 
   */
  CartesianPosition getTargetToReach() const { return( __targets.front()); };
  /**
   * @brief Remove the target reached (thread safe)
   * 
   */
  void targetReached() { 
    std::lock_guard<std::mutex> lock(__tracker_guard);
    __targets.pop_front(); 
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

private:  
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

};

#endif /* F1EC95FA_2EBE_49E9_8BA2_752CE00097F9 */
