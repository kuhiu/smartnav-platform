#include <Compass.hpp>

#include <math.h>

//#define DEBUG_COMPASS 1
#ifdef DEBUG_COMPASS
#define DEBUG_PRINT(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...) do {} while (0)
#endif

Compass::Compass() {
  int ret;

  __fd = open(__DRIVER, O_WRONLY);
  if (__fd == -1) {
    std::ostringstream err;
    err << "Error: driver " << __DRIVER << " could not be open.";
    std::runtime_error(err.str());
  }
  ret = ioctl(__fd, __COMPASS_ADDR);
  if (ret < 0) {
    std::ostringstream err;
    err << "Error: ioctl: " << strerror(errno);
    std::runtime_error(err.str());
  }
  // Create sma 
  __sma = std::make_shared<SimpleMovingAverage>(__SMA_LEN);
  // Calibrate compass
  __calibrate();
  // Start thread
  __is_running = true;
  __compass_thread = std::thread(&Compass::__readCompass, this);
};

Compass::~Compass() {
	__is_running = false;
	__compass_thread.join();
	close(__fd);
	DEBUG_PRINT("Read compass thread stopped.\n");
}

void Compass::__readCompass() {
  float fx;
  float fy;
  float heading;

  while (__is_running) {
    std::shared_ptr<Compass::CompassValues> sample = __readSample();
    if (sample != nullptr) {
      sample->raw_x = sample->raw_x - 
              ((__calibration_values.x_high + __calibration_values.x_low) / 2);
      sample->raw_y = sample->raw_y - (
              (__calibration_values.y_high + __calibration_values.y_low) / 2);
      fx = (float) sample->raw_x / 
        ( (float)__calibration_values.x_high - (float)__calibration_values.x_low);
      fy = (float) sample->raw_y / 
        ( (float)__calibration_values.y_high - (float) __calibration_values.y_low);
      heading = 180.0 * atan2(fy,fx) / M_PI ;
      if(heading <= 0) 
        heading += 360;
      DEBUG_PRINT("Heading: %f \n", heading);
      {
        std::scoped_lock lock(__m);
        __sma->addData(heading);
      }
    }
  }
}

std::shared_ptr<Compass::CompassValues> Compass::__readSample() {
  int status;
  std::shared_ptr<CompassValues> ret;

  status = i2c_smbus_read_byte_data (__fd , Registers::QMC5883L_STATUS);
  if (status == 0X02) {  
    DEBUG_PRINT("HMC5883L: Overflow.\n");
    ret = nullptr;
  }
  else if (status == 0X04) { 
    DEBUG_PRINT("HMC5883L: Data skipped.\n");
    ret = nullptr;
  }
  else if(status == 0X01) {  
    DEBUG_PRINT("New data available.\n");
    ret->raw_x = __getRawValue(Axes::X_AXIS);
    ret->raw_y = __getRawValue(Axes::Y_AXIS);
    ret->raw_z = __getRawValue(Axes::Z_AXIS);
    DEBUG_PRINT("HMC5883L: new data: raw_x: %d, raw_y: %d, raw_z: %d.\n", ret->raw_x, ret->raw_y, ret->raw_z);
  }
  else {
    DEBUG_PRINT("Data no available.\n");
    ret = nullptr;
  }
  return ret;
}

void Compass::__calibrate() {
  // Initialization of calibration values
  __calibration_values.x_high = std::numeric_limits<int>::max();
  __calibration_values.x_low = std::numeric_limits<int>::min();
  __calibration_values.y_high = std::numeric_limits<int>::max();
  __calibration_values.y_low = std::numeric_limits<int>::min();

  for (int i=0; i<__SAMPLES_TO_CALIB; i++) {
    std::shared_ptr<Compass::CompassValues> ret = __readSample();
    // Search max and min values for x values 
    if(ret->raw_x < __calibration_values.x_low) 
      __calibration_values.x_low = ret->raw_x;
    if(ret->raw_x > __calibration_values.x_high) 
      __calibration_values.x_high = ret->raw_x;
    // Search max and min values for y values 
    if(ret->raw_y < __calibration_values.y_low) 
      __calibration_values.y_low = ret->raw_y;
    if(ret->raw_y > __calibration_values.y_high) 
      __calibration_values.y_high = ret->raw_y;
  }
}