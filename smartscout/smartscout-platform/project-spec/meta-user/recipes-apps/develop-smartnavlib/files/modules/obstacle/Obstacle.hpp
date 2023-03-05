#ifndef BD4C42A3_637A_4380_9C17_15346BBBE48F
#define BD4C42A3_637A_4380_9C17_15346BBBE48F

#include <PositionEstimator.hpp>

class Obstacle {
public:
  /** Obstacle constructor */
  Obstacle(PositionEstimator::cartesianPosition position, PositionEstimator::cartesianPosition leftmost_point,
      PositionEstimator::cartesianPosition rightmost_point) : 
      __position(position), __leftmost_point(leftmost_point), __rightmost_point(rightmost_point) {};
  /** Obstacle destructor */
  ~Obstacle() = default;
  /**
   * @brief Get the Position object
   * 
   * @return PositionEstimator::cartesianPosition 
   */
  PositionEstimator::cartesianPosition getPosition() const { return __position; };
  /**
   * @brief Get the Leftmost Point object
   * 
   * @return Dimensions 
   */
  PositionEstimator::cartesianPosition getLeftmostPoint() const { return __leftmost_point; };
  /**
   * @brief Get the Rightmost Point object
   * 
   * @return Dimensions 
   */
  PositionEstimator::cartesianPosition getRightmostPoint() const { return __rightmost_point; };

private:
  /** Obstacle's position */
  PositionEstimator::cartesianPosition __position;
  /** Leftmost point of the obstacle's width */
  PositionEstimator::cartesianPosition __leftmost_point;
  /** Rightmost point of the obstacle's width */
  PositionEstimator::cartesianPosition __rightmost_point;

};


#endif /* BD4C42A3_637A_4380_9C17_15346BBBE48F */