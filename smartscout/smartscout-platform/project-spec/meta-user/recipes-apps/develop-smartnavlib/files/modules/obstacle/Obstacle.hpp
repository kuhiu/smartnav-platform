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
    float obj_width_cm = 16;
    float dy;

    PolarPosition obstacle_polar(curr_robot_angle, distance_to_obstacle);
    __position = PositionEstimator::polarToCartesian(obstacle_polar);
    __position = __position + curr_position;
    // Leftmost point of the obstacle's width 
    dy = 0.5-recognized_object.xmin;
    float left_distance = std::sqrt(std::pow(distance_to_obstacle, 2) + std::pow(dy*obj_width_cm, 2));
    float left_angle = (atan2(dy*obj_width_cm, distance_to_obstacle)*180/M_PI) + curr_robot_angle;
    // Create most left point
    PolarPosition leftmost_obstacle_point_pol(left_angle, left_distance);
    __leftmost_point = PositionEstimator::polarToCartesian(leftmost_obstacle_point_pol);
    __leftmost_point = __leftmost_point + curr_position;

    // Rightmost point of the obstacle's width 
    dy = recognized_object.xmax-0.5;
    float right_distance = std::sqrt(std::pow(distance_to_obstacle, 2) + std::pow(dy*obj_width_cm, 2));
    float right_angle = atan2(-dy*obj_width_cm, distance_to_obstacle)*180/M_PI + curr_robot_angle;
    PolarPosition rightmost_obstacle_point_pol(right_angle, right_distance);
    __rightmost_point = PositionEstimator::polarToCartesian(rightmost_obstacle_point_pol);
    __rightmost_point = __rightmost_point + curr_position;

    float dtita = rightmost_obstacle_point_pol.angle - obstacle_polar.angle;
    float dalfa = leftmost_obstacle_point_pol.angle - obstacle_polar.angle;
    if (std::abs(dtita) > std::abs(dalfa)) {
      __furthest_point = __rightmost_point; 
      __closest_point = __leftmost_point;
    }
    else {
      __furthest_point = __leftmost_point; 
      __closest_point = __rightmost_point;
    }

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
   * @brief Get the Closest Point object
   * 
   * @return CartesianPosition 
   */
  CartesianPosition getClosestPoint() const { return __closest_point; };
  /**
   * @brief Get the Furthest Point object
   * 
   * @return CartesianPosition 
   */
  CartesianPosition getFurthestPoint() const { return __furthest_point; };
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
  /** Closest point */
  CartesianPosition __closest_point;
  /** Furthest point */
  CartesianPosition __furthest_point;
};


#endif /* BD4C42A3_637A_4380_9C17_15346BBBE48F */
