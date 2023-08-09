#ifndef C4E00526_94EA_4FF2_8A5E_9B285CD4E27A
#define C4E00526_94EA_4FF2_8A5E_9B285CD4E27A

#include <nlohmann/json.hpp>

/** cartesianPosition struct */
struct CartesianPosition {
  /** X estimation [cm] */
  float x;
  /** Y estimation [cm] */
  float y;
  /** cartesianPosition constructor */
  CartesianPosition() = default;
  /** cartesianPosition constructor */
  CartesianPosition(float x, float y) : x(x), y(y) {};
  /**
   * @brief Convert the cartesian position to json
   * 
   * @return nlohmann::json 
   */
  nlohmann::json toJson() const {
    nlohmann::json json {
      {"x", x}, 
      {"y", y}
    };
    return json;
  };
  /**
   * @brief Plus operator 
   * 
   * @param other 
   * @return CartesianPosition 
   */
  CartesianPosition operator+(const CartesianPosition& other) const {
      return CartesianPosition(x + other.x, y + other.y);
  }
  /**
   * @brief Minus operator 
   * 
   * @param other 
   * @return CartesianPosition 
   */
  CartesianPosition operator-(const CartesianPosition& other) const {
    return CartesianPosition(x - other.x, y - other.y);
  }
};

#endif /* C4E00526_94EA_4FF2_8A5E_9B285CD4E27A */

