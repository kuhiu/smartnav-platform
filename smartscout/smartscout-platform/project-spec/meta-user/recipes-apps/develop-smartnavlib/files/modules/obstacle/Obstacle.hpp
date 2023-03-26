#ifndef BD4C42A3_637A_4380_9C17_15346BBBE48F
#define BD4C42A3_637A_4380_9C17_15346BBBE48F

#include <CartesionPosition.hpp>
#include <RecognitionResult.hpp>
#include <PolarPosition.hpp>
#include <PositionEstimator.hpp>

#include <nlohmann/json.hpp>

class Obstacle {
public:
  /** Obstacle constructor */
  Obstacle(float curr_robot_angle, float distance_to_obstacle, CartesianPosition curr_position, RecognitionResult recognized_object) {
        PolarPosition obstacle_polar(curr_robot_angle, distance_to_obstacle);
        __position = PositionEstimator::polarToCartesian(obstacle_polar);
        __position.x = __position.x + curr_position.x;
        __position.y = __position.y + curr_position.y;
        // Width of the obstacle to avoid 
        // Leftmost point of the obstacle's width 
        PolarPosition leftmost_obstacle_point_pol((atan2((0.5-recognized_object.xmin)*16, distance_to_obstacle)*180/M_PI) + curr_robot_angle, 
            (std::sqrt(std::pow(distance_to_obstacle, 2) + std::pow((0.5-recognized_object.xmin)*16, 2))) );
        __leftmost_point = PositionEstimator::polarToCartesian(leftmost_obstacle_point_pol);
        __leftmost_point.x = __leftmost_point.x + curr_position.x;
        __leftmost_point.y = __leftmost_point.y + curr_position.y;
        // Rightmost point of the obstacle's width 
        PolarPosition rightmost_obstacle_point_pol((atan2(-(recognized_object.xmax-0.5)*16, distance_to_obstacle)*180/M_PI) + curr_robot_angle, 
            std::sqrt(std::pow(distance_to_obstacle, 2) + std::pow((recognized_object.xmax-0.5)*16, 2)));
        __rightmost_point = PositionEstimator::polarToCartesian(rightmost_obstacle_point_pol);
        __rightmost_point.x = __rightmost_point.x + curr_position.x;
        __rightmost_point.y = __rightmost_point.y + curr_position.y;
      };
  /** Obstacle destructor */
  ~Obstacle() = default;
  /**
   * @brief Get the Position object
   * 
   * @return CartesianPosition 
   */
  CartesianPosition getPosition() const { return __position; };
  /**
   * @brief Get the Leftmost Point object
   * 
   * @return Dimensions 
   */
  CartesianPosition getLeftmostPoint() const { return __leftmost_point; };
  /**
   * @brief Get the Rightmost Point object
   * 
   * @return Dimensions 
   */
  CartesianPosition getRightmostPoint() const { return __rightmost_point; };
  /**
   * @brief Convert the obstacle object to JSON
   * 
   * @param obstacle_num 
   * @return nlohmann::json 
   */
  nlohmann::json toJson(int obstacle_num) const {
    nlohmann::json ret;

    std::string name = "obstacle_n" + std::to_string(obstacle_num);
    ret[name]["position"] = __position.toJson();
    ret[name]["leftmost"] = __leftmost_point.toJson();
    ret[name]["rightmost"] = __rightmost_point.toJson();
    return ret;
  }

private:
  /** Obstacle's position */
  CartesianPosition __position;
  /** Leftmost point of the obstacle's width */
  CartesianPosition __leftmost_point;
  /** Rightmost point of the obstacle's width */
  CartesianPosition __rightmost_point;

};


#endif /* BD4C42A3_637A_4380_9C17_15346BBBE48F */
