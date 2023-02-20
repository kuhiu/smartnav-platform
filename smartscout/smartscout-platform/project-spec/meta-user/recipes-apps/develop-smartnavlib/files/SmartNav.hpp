#ifndef A75E67F7_9C3F_4370_A541_4B1DB5BD2F02
#define A75E67F7_9C3F_4370_A541_4B1DB5BD2F02

#include <fstream>
#include <iostream>
#include <memory>
#include <thread>

#include <CaptureFrame.hpp>
#include <Compass.hpp>
#include <Driver.hpp>
#include <DistanceSensors.hpp>
#include <FuzzyControlSystem.hpp>
#include <Headlights.hpp>

class SmartNav {
public:
  /** Smartnav constructor */
  SmartNav();
  /** Smartnav destructor */
  ~SmartNav();

private:
  /** JSON file which describes the fuzzy system */
  static constexpr auto __FUZZY_JSON{"/usr/bin/fuzzy_system_v1.json"};
  /** Thread status */
  bool __is_running;
  /** Thread navigation */
  std::thread __navigation_thread;
  /** Driver object  */
	Driver __driver;
  /** Capture frame object */
  std::shared_ptr<CaptureFrame> __capture_frame;
  /** Headlights object */
  Headlights __headlights;
	/** Distance sensor object */
	DistanceSensors __distance_sensor;
  /** Compass object */
  Compass __compass;
  /** Fuzzy control system object */
  std::shared_ptr<FuzzyControlSystem> __fuzzy_system;
  /**
   * @brief Frame callback
   * 
   * @param img 
   * @param ctx 
   */
  static void __frame_callback(std::shared_ptr<VirtualImage> img, void* ctx);
  /**
   * @brief Navigate
   * 
   */
  void __navigation();
  
};

#endif /* DBCD007B_2AE4_4807_BE39_8D3ADAFADDB8 */

