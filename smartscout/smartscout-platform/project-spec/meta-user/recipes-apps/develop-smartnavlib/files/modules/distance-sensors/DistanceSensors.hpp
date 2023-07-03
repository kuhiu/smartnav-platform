#ifndef __DISTANCESENSORS_H__
#define __DISTANCESENSORS_H__

#include <atomic>
#include <mutex>
#include <thread>
#include <vector>

#include <SimpleMovingAverage.hpp>
class DistanceSensors {
public:
  /**
   * @brief Get the Instance of the DistanceSensors
   * 
   * @return DistanceSensors* 
   */
  static DistanceSensors* getInstance();
  /**
   * @brief Deleting copy constructor
   * 
   * @param obj 
   */
  DistanceSensors(const DistanceSensors& obj) = delete;
  /**
   * @brief Singleton should not be assignable
   * 
   */
  void operator=(const DistanceSensors&) = delete;
	/**
	 * @brief Get the Distances to objects
	 * 
	 * @return std::vector<int> 
	 */
	std::vector<int> getDistances();
    
private:
	/** Driver directory */
	static constexpr auto __HC_SR04_DRIVER_DIR = "/dev/hcsr04";
	/** Number of sensors */
	static const int __NRO_SENSORS = 3;
	/** One queue per sensor to calculate the sma */
	std::vector<SimpleMovingAverage> __sma_vec;
	/** Driver file descriptor */
	int __fd;
	/** Reading distance sensor thread */
	std::thread __reading_thread;
	/** Thread status */
	std::atomic<bool> __is_running;
	/** Singleton instance */
	static DistanceSensors* __instance;
	/** DistanceSensor constructor */
	DistanceSensors();
	/** DistanceSensor destructor */
	~DistanceSensors();
	/** Read distances from driver */
	void __readDistance();
	/**
	 * @brief Time to distance
	 * 
	 * @param time 
	 * @return float 
	 */
	float __timeToDistance(float time);

};


#endif // __DISTANCESENSORS_H__