#ifndef CA3B3897_B288_488A_A614_DDBFCDA9CF19
#define CA3B3897_B288_488A_A614_DDBFCDA9CF19

#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

#include <RecognitionResult.hpp>
#include <Obstacle.hpp>
#include <CartesionPosition.hpp>

#include <nlohmann/json.hpp>

class utilities {
public:
  struct metadata {
    /** Timestamp */
    std::vector<int> __timestamp;
    /** Obstacles */
    std::vector<Obstacle> __obstacles;
    /** Angle: Absolute angle to where the robot was looking */
    std::vector<float> __angle_history;
    /** Origin point */
    CartesianPosition __origin;
    /** Destination point */
    CartesianPosition __destination;
    /** Historical position points */
    std::vector<CartesianPosition> __position_history;
    /** Historical arrival position: Relative to the currect position */
    std::vector<CartesianPosition> __arrival_point_history;
    /** Recognized objects */
    std::vector<RecognitionResult> __recognized_object;
    /** Metadata constructor */
    metadata(std::vector<CartesianPosition> position_history,
      std::vector<float> angle_history, 
      std::vector<CartesianPosition> arrival_point_history,
      std::vector<int> timestamp, 
      CartesianPosition origin, 
      CartesianPosition destination, 
      std::vector<Obstacle> obstacles,
      std::vector<RecognitionResult> recognized_object) : __position_history(position_history),
          __angle_history(angle_history), __arrival_point_history(arrival_point_history), 
          __timestamp(timestamp), __origin(origin), __destination(destination), __obstacles(obstacles),
          __recognized_object(recognized_object) {};
  };
  /** Utilities constructor */
  utilities() {
    __file.open(__FILE, std::ios::trunc | std::ios::out);
  };
  /** Utilities destructor */
  ~utilities() {
    __file.close();
  };
  /**
   * @brief Append the metada to the history file 
   * 
   * @param metadata 
   */
  void appedToFile(metadata metadata) {
    int i = 0;
    int j = 0;

    nlohmann::json metadata_json;
    metadata_json["steps"];
    for (const CartesianPosition &position : metadata.__position_history) {
      std::string name = "position_n" + std::to_string(i);
      metadata_json["steps"][name]["position"] = position.toJson();
      metadata_json["steps"][name]["timestamp"] = metadata.__timestamp[i];
      metadata_json["steps"][name]["angles"] = metadata.__angle_history[i];
      metadata_json["steps"][name]["arrival_point"] = metadata.__arrival_point_history[i].toJson();
      i++;
    }
    metadata_json["destination"] = metadata.__destination.toJson();
    metadata_json["origin"] = metadata.__origin.toJson();
    metadata_json["obstacles"];
    for (auto obstacle :  metadata.__obstacles) {
      std::string name = "obstacle_n" + std::to_string(j);
      metadata_json["obstacles"][name]["position"] = obstacle.getPosition().toJson();
      metadata_json["obstacles"][name]["leftmost"] = obstacle.getLeftmostPoint().toJson();
      metadata_json["obstacles"][name]["rightmost"] = obstacle.getRightmostPoint().toJson();
      j++;
    }
    metadata_json["recognized_object"];
    for (const auto &recog_object : metadata.__recognized_object) {
      std::string name = "recognized_object_n" + std::to_string(j);
      metadata_json["recognized_object"][name] = recog_object.toJson();
    }
    __file << metadata_json;
  };

private:
  /** File name where the history positions are saved */
  static constexpr const char *__FILE = {"/tmp/history.json"};
  /** File stream */
  std::ofstream __file;

};

#endif /* CA3B3897_B288_488A_A614_DDBFCDA9CF19 */