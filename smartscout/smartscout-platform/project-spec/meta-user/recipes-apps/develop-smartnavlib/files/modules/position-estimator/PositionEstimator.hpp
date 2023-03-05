#ifndef CB735F5E_BE3E_43A6_BBFC_3D44E38ADF1E
#define CB735F5E_BE3E_43A6_BBFC_3D44E38ADF1E

#define _USE_MATH_DEFINES
#include <math.h>

#include <memory>
#include <mutex>
#include <queue>

#include <Compass.hpp>
#include <mailbox.hpp>
#include <SimpleMovingAverage.hpp>

#include <nlohmann/json.hpp>

class PositionEstimator {
public:
  /** cartesianPosition struct */
  struct cartesianPosition {
    /** X estimation [cm] */
    float x;
    /** Y estimation [cm] */
    float y;
    /** cartesianPosition constructor */
    cartesianPosition() = default;
    /** cartesianPosition constructor */
    cartesianPosition(float x, float y) : x(x), y(y) {};
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

  };
  /** polarPosition struct */
  struct polarPosition {
    /** angle estimation [degree] */
    float angle;
    /** distance estimation [cm] */
    float distance;
    /** polarPosition constructor */
    polarPosition() = default;
    /** polarPosition constructor */
    polarPosition(float angle, float distance) : angle(angle), distance(distance) {};
  
  };
  /** PositionEstimator constructor */
  PositionEstimator();
  /** PositionEstimator destructor */
  ~PositionEstimator();
  /**
   * @brief Get the Current Position object
   * 
   * @return polarPosition 
   */
  cartesianPosition getCurrentPosition();
  /**
   * @brief Get the Current Angle object
   * 
   * @return float 
   */
  float getCurrentAngle() { return __compass.getValue(); };
  /**
   * @brief Axies rotation
   * 
   * @param point 
   * @return cartesianPosition 
   */
  cartesianPosition relativizePoint(cartesianPosition point) {
    cartesianPosition ret;
    float angle = __compass.getValue();
    
    angle = angle * M_PI / 180.0;
    ret.x = point.x * cos(angle) - point.y * sin(angle);
    ret.y = point.x * sin(angle) + point.y * cos(angle);
    return ret;
  };
  /**
   * @brief Convert the cartesian position to the polar position
   * 
   * @param cartesian 
   * @return polarPosition 
   */
  polarPosition cartensianToPolar(cartesianPosition cartesian) {
    polarPosition ret;

    ret.angle = atan2(cartesian.y, cartesian.x) * 180.0 / M_PI; 
    ret.distance = std::sqrt(std::pow(cartesian.x, 2) + std::pow(cartesian.y, 2));
    return ret;
  };
  /**
   * @brief Conver the polar position to the cartesian position 
   * 
   * @param polar 
   * @return cartesianPosition 
   */
  cartesianPosition polarToCartesian(polarPosition polar) {
    cartesianPosition ret;

    ret.x = polar.distance*cos(__degrees_to_radians(polar.angle));
    ret.y = polar.distance*sin(__degrees_to_radians(polar.angle));
    return ret;
  };

private:
  /** SMA length */
  const int __QUEUE_LEN = 2;
  /** Thread status */
  bool __is_running;
  /** Mailbox object */
  mailbox __mailbox;
  /** Compass object */
  Compass __compass;
  /** Queue for encoder 1 counts */
  std::queue<int> encoder1_queue;
  /** Queue for encoder 2 counts */
  std::queue<int> encoder2_queue;
  /** Traveled distance */
  float __traveled_distance;
  /** SMA guard */
  std::mutex __m;
  /** Encoders thread */
  std::thread __encoders_thread; 
  /** Current position */
  cartesianPosition __curr_position;
  /**
   * @brief Read encoders
   * 
   */
  void __readEncoders();
  /**
   * @brief Get traveled distance value (thread safe)
   * 
   * @return float 
   */
  float __getTraveledDistance() {
    float ret;
    {
      std::lock_guard<std::mutex> lock(__m);
      ret = __traveled_distance;
    }
    return ret;
  };
  /**
   * @brief Encoder count to distance [cm] 
   * 
   * @param count 
   * @return float 
   */
  float __countToDistance(int count) { return ((3.305*2*M_PI*(float)count)/(float)20); }
  /**
   * @brief Degree to radians
   * 
   * @param degrees 
   * @return float 
   */
  float __degrees_to_radians(float degrees) { return degrees * (M_PI / 180); }

};

#endif /* CB735F5E_BE3E_43A6_BBFC_3D44E38ADF1E */