#ifndef __DISTANCESENSORS_H__
#define __DISTANCESENSORS_H__

#include <atomic>
#include <mutex>
#include <thread>
#include <vector>

class DistanceSensors {
public:
	/** DistanceSensor constructor */
	DistanceSensors();
	/** DistanceSensor destructor */
	~DistanceSensors();
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
	const int __NRO_SENSORS = 3;
	/** Number of samples to average */
	int __nro_samples_to_average = 3;
	/** Driver file descriptor */
	int __fd;
	/** Distances from distance sensors */
	std::vector<std::vector<float>> __distance_from_sensors; 
	/** Measures guard */
	std::mutex __measures_guard;
	/** Reading distance sensor thread */
	std::thread __reading_thread;
	/** Thread status */
	std::atomic<bool> __is_running;
	/** Read distances from driver */
	void __readDistance();
	/**
	 * @brief Average of al samples taken
	 * 
	 * @return std::vector<int> 
	 */
	std::vector<int> __averageOfDistances();
	/**
	 * @brief Time to distance
	 * 
	 * @param time 
	 * @return float 
	 */
	float __timeToDistance(float time);

};


#endif // __DISTANCESENSORS_H__