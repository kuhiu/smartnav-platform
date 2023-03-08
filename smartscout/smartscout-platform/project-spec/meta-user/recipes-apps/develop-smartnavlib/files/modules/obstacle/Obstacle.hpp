#ifndef BD4C42A3_637A_4380_9C17_15346BBBE48F
#define BD4C42A3_637A_4380_9C17_15346BBBE48F

#include <CartesionPosition.hpp>

class Obstacle {
public:
  /** Obstacle constructor */
  Obstacle(CartesianPosition position, CartesianPosition leftmost_point,
      CartesianPosition rightmost_point) : 
      __position(position), __leftmost_point(leftmost_point), __rightmost_point(rightmost_point) {};
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

private:
  /** Obstacle's position */
  CartesianPosition __position;
  /** Leftmost point of the obstacle's width */
  CartesianPosition __leftmost_point;
  /** Rightmost point of the obstacle's width */
  CartesianPosition __rightmost_point;

};


#endif /* BD4C42A3_637A_4380_9C17_15346BBBE48F */
