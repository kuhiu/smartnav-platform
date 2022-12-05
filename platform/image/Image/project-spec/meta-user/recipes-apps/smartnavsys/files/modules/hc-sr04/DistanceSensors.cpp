#include "DistanceSensors.hpp"

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <chrono>
#include <numeric>
#include <sstream>
#include <stdexcept>

#define HCSR04_IOC_NMAGICO 'c'
#define HCSR04_IOC_TRIGGER _IO(HCSR04_IOC_NMAGICO, 1)

DistanceSensors::DistanceSensors() {
	printf("Distance sensor constructor.\n");
	if ( (__fd = open(__HC_SR04_DRIVER_DIR, O_RDONLY)) == -1){
		std::stringstream err;
		err << "Open fail: " << strerror(errno);
		throw std::runtime_error(err.str());
	}

	for(int i=0; i < __NRO_SENSORS; i++) {
		std::vector<float> __new_sensor;
		for(int j=0; j < __nro_samples_to_average; j++) {
			float __new_sample = {0.0};
			__new_sensor.push_back(__new_sample);
		}
		__distance_from_sensors.push_back(__new_sensor);
	}
	__is_running = true;
	printf("Run read distance thread.\n");
	__reading_thread = std::thread(&DistanceSensors::__readDistance, this);
}

DistanceSensors::~DistanceSensors() {
	__is_running = false;
	__reading_thread.join();
	close(__fd);
}

std::vector<int> DistanceSensors::getDistances() { 
	// Thread safe
	std::lock_guard<std::mutex> lock(__measures_guard);
	return __averageOfDistances(); 
}

void DistanceSensors::__readDistance() {
	while(__is_running) {
		static int sample_index = 0;
		int samples_from_sensors[__NRO_SENSORS]; 

		if (sample_index == __nro_samples_to_average) 
			sample_index = 0;

		// Read the distance of each sensor 
		samples_from_sensors[0] = ioctl(__fd, HCSR04_IOC_TRIGGER, 1);
		if ( samples_from_sensors[0] == -1) {
			throw std::runtime_error("Error reading distance sensors");
		}
		printf("Sensor 1. Time %d. Distance %f.\n", samples_from_sensors[0], __timeToDistance((float)samples_from_sensors[0]));

		samples_from_sensors[1] = ioctl(__fd, HCSR04_IOC_TRIGGER, 2);
		if ( samples_from_sensors[1] == -1) {
			throw std::runtime_error("Error reading distance sensors");
		}
		printf("Sensor 2. Time %d. Distance %f.\n", samples_from_sensors[1], __timeToDistance((float)samples_from_sensors[1]));

		samples_from_sensors[2] = ioctl(__fd, HCSR04_IOC_TRIGGER, 3);
		if ( samples_from_sensors[2] == -1) {
			throw std::runtime_error("Error reading distance sensors");
		}
		printf("Sensor 3. Time %d. Distance %f.\n", samples_from_sensors[2], __timeToDistance((float)samples_from_sensors[2]));

		{	// Thread safe
			std::lock_guard<std::mutex> lock (__measures_guard);
			for(int sensor_index=0; sensor_index < __NRO_SENSORS; sensor_index++) 
				__distance_from_sensors[sensor_index][sample_index] = __timeToDistance((float)samples_from_sensors[sensor_index]);
		}
		sample_index++;
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
	}
}

float DistanceSensors::__timeToDistance(float time) {
    float distance = time*(float)0.01715;

    if ( (distance > 500) || (distance < 0) )
        return 500;
    return distance;    
}

std::vector<int> DistanceSensors::__averageOfDistances(void) {
	std::vector<int> averages;

	for(int sensor_index=0; sensor_index < __NRO_SENSORS; sensor_index++) {
		 int average = std::accumulate(	__distance_from_sensors[sensor_index].begin(), 
																		__distance_from_sensors[sensor_index].end(), 
																		0.0);
		average /= __distance_from_sensors[sensor_index].size();
		averages.push_back(average);
	}
	return averages;
}

