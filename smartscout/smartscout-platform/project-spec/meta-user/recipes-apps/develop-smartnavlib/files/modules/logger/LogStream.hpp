#ifndef __LOGSTREAM_H__
#define __LOGSTREAM_H__

#include <sstream>

#include "LogLevels.hpp"

class Logger;

class LogStream : public std::ostringstream {  
public:
  /** LogStream constructor */
  LogStream(Logger& logger, LogLevels log_level);
  /** LogStream destructor */
  ~LogStream();
  /**
   * @brief Get the string of the level
   * 
   * @return std::string 
   */
  std::string levelToString();

private:
  /** Logger instance */
  Logger &__logger_instance;
  /** Log level */
  LogLevels __log_level;

};


#endif // __LOGSTREAM_H__