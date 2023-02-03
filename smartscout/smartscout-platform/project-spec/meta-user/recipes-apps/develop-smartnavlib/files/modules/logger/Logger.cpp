#include "Logger.hpp"

#include <iostream>

Logger::Logger() { 
	__is_running = true;
	__print_thread = std::thread(&Logger::__printRoutine, this, std::chrono::milliseconds(50)); 
}

Logger::~Logger() {
  __is_running = false;
  __print_thread.join();
}

void Logger::push(std::string fmt_msg) {
	std::unique_lock<std::mutex> lock(__queue_guard);
	__msgs_queue.push(fmt_msg);
}

void Logger::__printRoutine(Logger *instance, std::chrono::duration<double, std::milli> interval) {
	while(instance->__is_running) {
		if (!instance->__isQueueEmpty()) {
			auto start_measure_time = std::chrono::steady_clock::now();
			{	// Thread safe print
				std::unique_lock<std::mutex> lock(instance->__queue_guard);
				while(!instance->__isQueueEmpty()) {
					std::cout << instance->__msgs_queue.front() << std::endl;
					instance->__msgs_queue.pop();
				}
			}
			auto end_measure_time = std::chrono::steady_clock::now();
			std::chrono::duration<double, std::milli> time_took = end_measure_time - start_measure_time;

			if(time_took < interval && instance->__is_running) {
				std::this_thread::sleep_for(interval - time_took);
			}
		}
	}
}

bool Logger::__isQueueEmpty() { return (__msgs_queue.empty()); }