#ifndef A2F94708_82E8_4C9B_BC30_0557D318208D
#define A2F94708_82E8_4C9B_BC30_0557D318208D

#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <thread>

#include <Tracker.hpp>

class Reporter {
public:
  /** Reporter constructor */
  Reporter(std::shared_ptr<Tracker> tracker) : __tracker(tracker) {
    __file.open(__FILE, std::ios::trunc | std::ios::out);
    // Start thread
    __is_running = true;
    __reporter_thread = std::thread(&Reporter::__report, this);
  };
  /** Reporter destructor */
  ~Reporter() {
    __is_running = false;
	  __reporter_thread.join();
	  __file.close();
  };

private:
  /** File name where the history positions are saved */
  static constexpr const char *__FILE = {"/home/root/history.json"};
  /** Tracker object */
  const std::shared_ptr<Tracker> __tracker;
  /** File stream */
  std::ofstream __file;
  /** Thread status */
  bool __is_running = false;
  /** Thread */
  std::thread __reporter_thread;
  /**
   * @brief Report the status of the tracker
   * 
   */
  void __report() {
    while (__is_running) {
      if (__file) {
        __file.close();
        __file.open(__FILE, std::ios::trunc | std::ios::out);
      }
      __file << std::setw(4) << __tracker->toJson() << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(2));
    }
  };

};




#endif /* A2F94708_82E8_4C9B_BC30_0557D318208D */
