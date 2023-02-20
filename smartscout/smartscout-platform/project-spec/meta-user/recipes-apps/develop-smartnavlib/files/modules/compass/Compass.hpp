#ifndef BE0BC7D9_199D_4452_AF76_CAC6D7DD76AA
#define BE0BC7D9_199D_4452_AF76_CAC6D7DD76AA

extern "C" {
  #include <linux/i2c-dev.h>
  #include <i2c/smbus.h>
}

#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <memory>
#include <mutex>
#include <sstream>
#include <stdexcept>
#include <thread>

#include <SimpleMovingAverage.hpp>

class Compass {
public:
  /** Calibrartion values */
  struct CalibrationValues {
    // Lower X calibration value
    int x_low;
    // Lower Y calibration value
    int y_low;
    // Higher X calibration value
    int x_high;
    // Higher Y calibration value
    int y_high;

  };
  /** Raw values of the compass */
  struct CompassValues {
    // Raw x value from compass
    int raw_x;
    // Raw y value from compass
    int raw_y;
    // Raw z value from compass
    int raw_z;

  };
  /** Axes */
  enum Axes {
    // X axis
    X_AXIS = 0,
    // Y axis
    Y_AXIS,
    // Z axis
    Z_AXIS,
  };
  /** Compass constructor */
  Compass();
  /** Compass destructor */
  ~Compass();
  /**
   * @brief Get compass value (thread safe)
   * 
   * @return float 
   */
  float getValue() {
    float ret;
    {
      std::lock_guard<std::mutex> lock(__m);
      ret = __sma->getMean();
    }
    return ret;
  };

private:
  /** Number of samples to calibrate the compass */
  const int __SAMPLES_TO_CALIB = 50;
  /** Compass i2c address */
  const uint32_t __COMPASS_ADDR = 0x0D; 
  /** Driver name */
  static constexpr auto __DRIVER{"/dev/i2c-0"}; 
  /** SMA lenght */
  const int __SMA_LEN = 3;
  /** Driver file descriptor */
  int __fd;
  /** Calibration values */
  CalibrationValues __calibration_values;
  /**
   * @brief Calibrate the compass
   * 
   * @return CalibrationValues 
   */
  void __calibrate();
  /**
   * @brief Read compass thread function
   * 
   */
  void __readCompass();
  /**
   * @brief Read samples from the compass
   * 
   * @return std::shared_ptr<Compass::CompassValues> 
   */
  std::shared_ptr<Compass::CompassValues> __readSample();
  /** Compass thread */
  std::thread __compass_thread;
  /** Thread status */
  bool __is_running;
  /** SimpleMovingAverage */
	std::shared_ptr<SimpleMovingAverage> __sma;
  /** SMA guard */
  std::mutex __m;
  /**
   * @brief Get raw axis value
   * 
   * @param axis 
   * @return int 
   */
  int __getRawValue(Axes axis);

};

#endif /* BE0BC7D9_199D_4452_AF76_CAC6D7DD76AA */
