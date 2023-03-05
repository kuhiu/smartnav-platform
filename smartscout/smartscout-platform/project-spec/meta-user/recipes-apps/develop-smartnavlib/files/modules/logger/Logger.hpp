#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "LogLevels.hpp"

#include <atomic>
#include <queue>
#include <mutex>
#include <string>
#include <thread>

class Logger;

#include "LogStream.hpp"

class Logger {
public:
  /** Delete copy constructor */
  Logger(Logger const&) = delete;
  /** Delete assignnment operator */
  void operator=(Logger const&) = delete;
  /**
   * @brief This create Logger object and return a LogStream object
   * 
   * @param level 
   * @return LogStream 
   */
  static LogStream log(LogLevels level = LogLevels::Info) {
	  static Logger logger;
	  return LogStream(logger, level);
  }
  /**
   * @brief Push a new msg into the queue
   * 
   * @param new_msg 
   */
  void push(std::string new_msg);

private:
  /** Logger constructor */
  Logger();
  /** Logger destructor */
  ~Logger();
  /**
   * @brief Print routine
   * 
   * @param instance Logger instance
   * @param interval Time between printing 
   */
  static void __printRoutine(Logger *instance, std::chrono::duration<double, std::milli> interval); 
  /**
   * @brief Return queue state
   * 
   * @return true If queue is empty
   * @return false If queue is not empty
   */
  bool __isQueueEmpty();   
  /** Printer thread */
  std::thread __print_thread;
  /** Thread state */
  std::atomic<bool> __is_running;
  /** Message queue */
  std::queue<std::string> __msgs_queue;
  /** Message queue guard */
  std::mutex __queue_guard; 
  
};

#endif // __LOGGER_H__