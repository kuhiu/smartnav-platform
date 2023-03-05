#include "LogStream.hpp"
#include "Logger.hpp"

LogStream::LogStream(Logger& logger, LogLevels level) 
    : __logger_instance(logger), __log_level(level) {}

LogStream::~LogStream() { __logger_instance.push(levelToString() + str()); }

std::string LogStream::levelToString() {
  std::string string;
  switch(__log_level) {
    case LogLevels::Info: 
    string = "[INFO]"; 
    break;
    case LogLevels::Warning: 
    string = "[WARNING]"; 
    break;
    case LogLevels::Fatal: 
    string = "[FATAL]"; 
    break;
  }
  return string;    
}