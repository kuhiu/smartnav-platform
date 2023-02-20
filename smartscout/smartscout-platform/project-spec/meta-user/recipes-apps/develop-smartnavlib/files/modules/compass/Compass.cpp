#include <Compass.hpp>

#include <math.h>
#include <errno.h>
#include <string.h>

#include <chrono>

#include <Registers.hpp>

#define DEBUG_COMPASS 1
#if defined(DEBUG_COMPASS) 
 	#define DEBUG_PRINT(fmt, args...) printf( "DEBUG: %s:%d:%s(): " fmt, \
																						__FILE__, __LINE__, __func__, ##args)
#else
	#define DEBUG_PRINT(fmt, args...) /* Don't do anything in release builds */
#endif

constexpr const char *Compass::__DRIVER;

Compass::Compass() {
  int ret;

  __fd = open(__DRIVER, O_RDWR);
  if (__fd == -1) {
    std::ostringstream err;
    err << "Error: driver " << __DRIVER << " could not be open.";
    std::runtime_error(err.str());
  }
  ret = ioctl(__fd, I2C_SLAVE, __COMPASS_ADDR);
  if (ret < 0) {
    std::ostringstream err;
    err << "Error: ioctl: " << strerror(errno);
    std::runtime_error(err.str());
  }
  // Create sma 
  __sma = std::make_shared<SimpleMovingAverage>(__SMA_LEN);
  // Config compass (datasheet info)
  i2c_smbus_write_byte_data(__fd, Registers::QMC5883L_RESET, 0x01);
  i2c_smbus_write_byte_data(__fd, Registers::QMC5883L_CONFIG, 0x1D);
  // Calibrate compass
  __calibrate();
  DEBUG_PRINT("Compass calibrated: x_high: %d, x_low %d, y_high: %d, y_low: %d.\n", __calibration_values.x_high, 
    __calibration_values.x_low, __calibration_values.y_high, __calibration_values.y_low);
  std::this_thread::sleep_for(std::chrono::seconds(3));
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
      DEBUG_PRINT("raw_x : %d, raw_y %d.\n", sample->raw_x, sample->raw_y);
      sample->raw_x = sample->raw_x - 
              ((__calibration_values.x_high + __calibration_values.x_low) / 2);
      sample->raw_y = sample->raw_y - (
              (__calibration_values.y_high + __calibration_values.y_low) / 2);
      fx = (float) sample->raw_x / 
        ( (float)__calibration_values.x_high - (float)__calibration_values.x_low);
      fy = (float) sample->raw_y / 
        ( (float)__calibration_values.y_high - (float) __calibration_values.y_low);
      DEBUG_PRINT("fx : %f, fy %f.\n", fx, fy);
      heading = 180.0 * atan2(fy,fx) / M_PI ;
      if(heading <= 0) 
        heading += 360;
      DEBUG_PRINT("Heading: %f \n", heading);
      {
        std::lock_guard<std::mutex> lock(__m);
        __sma->addData(heading);
      }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

std::shared_ptr<Compass::CompassValues> Compass::__readSample() {
  int status;
  std::shared_ptr<CompassValues> ret;

  status = i2c_smbus_read_byte_data (__fd , Registers::QMC5883L_STATUS);
  if (status < 0) {
    DEBUG_PRINT("Failed read i2c bus. errno: %s.\n", strerror(errno));
    std::runtime_error("Failed reading byte from sensor.");
  }
  status = status & 0x07;
  DEBUG_PRINT("Status: 0x%08x.\n", status);
  if((status & Registers::QMC5883L_STATUS_DRDY)) {  
    DEBUG_PRINT("New data available.\n");
    ret = std::make_shared<CompassValues>();
    ret->raw_x = __getRawValue(Axes::X_AXIS);
    ret->raw_y = __getRawValue(Axes::Y_AXIS);
    ret->raw_z = __getRawValue(Axes::Z_AXIS);
    DEBUG_PRINT("HMC5883L: new data: raw_x: %d, raw_y: %d, raw_z: %d.\n", ret->raw_x, ret->raw_y, ret->raw_z);
  }
  else if((status & Registers::QMC5883L_STATUS_DOR)) {
    __getRawValue(Axes::X_AXIS);
    __getRawValue(Axes::Y_AXIS);
    __getRawValue(Axes::Z_AXIS);
  }  

  return ret;
}

void Compass::__calibrate() {
  // Initialization of calibration values
  __calibration_values.x_high = std::numeric_limits<int>::min();
  __calibration_values.x_low = std::numeric_limits<int>::max();
  __calibration_values.y_high = std::numeric_limits<int>::min();
  __calibration_values.y_low = std::numeric_limits<int>::max();

  for (int i=0; i<__SAMPLES_TO_CALIB; ) {
    std::shared_ptr<Compass::CompassValues> ret = __readSample();
    if (ret != nullptr) {
      i++;
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
    else 
      DEBUG_PRINT("Not readeable value.\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

int Compass::__getRawValue(Axes axis) {
  int raw = 0;
  int raw_lsb = 0;
  int raw_msb = 0;

  switch (axis) {
  case Axes::X_AXIS:
    raw_lsb = i2c_smbus_read_byte_data(__fd, Registers::QMC5883L_X_LSB);
    raw_msb = i2c_smbus_read_byte_data(__fd, Registers::QMC5883L_X_MSB);
    break;
  case Axes::Y_AXIS:
    raw_lsb = i2c_smbus_read_byte_data(__fd, Registers::QMC5883L_Y_LSB);
    raw_msb = i2c_smbus_read_byte_data(__fd, Registers::QMC5883L_Y_MSB);
    break;
  case Axes::Z_AXIS:
    raw_lsb = i2c_smbus_read_byte_data(__fd, Registers::QMC5883L_Z_LSB);
    raw_msb = i2c_smbus_read_byte_data(__fd, Registers::QMC5883L_Z_MSB);
    break;
  default:
    std::runtime_error("AXIS not supported.");
    break;
  }
  if (raw_lsb < 0) 
    std::runtime_error("Failed reading byte from sensor.");
  if (raw_msb < 0) 
    std::runtime_error("Failed reading byte from sensor.");
    
  raw = (raw_msb << 8) | raw_lsb;
  if (raw >= 0x8000)    // To get negative value
    raw = raw - 0x10000;
  
  return raw;
};