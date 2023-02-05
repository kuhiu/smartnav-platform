#ifndef A75E67F7_9C3F_4370_A541_4B1DB5BD2F02
#define A75E67F7_9C3F_4370_A541_4B1DB5BD2F02

#include <fstream>
#include <iostream>
#include <memory>
#include <thread>

#include "CaptureFrame.hpp"
#include "Driver.hpp"
#include "DistanceSensors.hpp"
#include "FuzzyControlSystem.hpp"
#include "Headlights.hpp"

class SmartNav {
public:
  /** Smartnav constructor */
  SmartNav() {
    // Parse fuzzy system file 
    std::ifstream fuzzy_system_file(__FUZZY_JSON);
    const json fuzzy_system_json = json::parse(fuzzy_system_file);
    // Create fuzzy control system object
    __fuzzy_system = std::make_shared<FuzzyControlSystem>(FuzzyControlSystem::parse(fuzzy_system_json));
    // Create Capture frame object
    __capture_frame = std::make_shared<CaptureFrame>(__frame_callback, 640, 480, CaptureFrame::pixelFormat::PIX_FMT_RGB24, 1);
    // Create a new thread
    __is_running = true;
    __navigation_thread = std::thread(&SmartNav::__navigation, this);
  }
  /** Smartnav destructor */
  ~SmartNav() {
    __driver.update(Driver::operationMode::OP_STOP, 0, 0);
    __is_running = false;
    __navigation_thread.join();
  };

private:
  /** JSON file which describes the fuzzy system */
  static constexpr const char *__FUZZY_JSON = {"/usr/bin/fuzzy_system_v1.json"};
  /** Thread status */
  bool __is_running;
  /** Thread navigation */
  std::thread __navigation_thread;
  /** Driver object  */
	Driver __driver;
  /** Capture frame object */
  std::shared_ptr<CaptureFrame> __capture_frame;
  /** Frame callback */
  static void __frame_callback(std::shared_ptr<VirtualImage> img, void* ctx) {
    CaptureFrame &context = *static_cast<CaptureFrame*> (ctx); 
    img->saveAsJpg("/tmp/test.jpg");
    context.frame_processor.processFrame(img);
  }
  /** Headlights object */
  Headlights __headlights;
	/** Distance sensor object */
	DistanceSensors __distance_sensor;
  /** Fuzzy control system object */
  std::shared_ptr<FuzzyControlSystem> __fuzzy_system;
  /** Navigate */
  void __navigation() {
    float yaw_variation;
    float speed_variation;

    while(__is_running) {
      std::vector<int> distances = __distance_sensor.getDistances();
      // Check number of distances 
      if (distances.size() != 3)
        throw std::runtime_error("Not three sensor outputs.");
      std::vector<std::pair<std::string, float>> inputs = { {"left_distance_sensor", (float)distances[0]},
                                                            {"center_distance_sensor", (float)distances[1]}, 
                                                            {"right_distance_sensor", (float)distances[2]},
                                                            {"lighting", (float)__capture_frame->getBrightness()}  };
      // Evaluate fuzzy system
      auto outputs = __fuzzy_system->evaluate(inputs);
      // Read outputs 
      for (FuzzyOutput &output : outputs) {
        if (output.getName() == "heading") 
          yaw_variation = output.defuzzification();
        else if (output.getName() == "car_speed")
          speed_variation = output.defuzzification();
        else if (output.getName() == "car_headlights")
          __headlights.update((uint32_t)output.defuzzification());
      }
      printf("Speed variation: %f. Yaw variation: %f.\n", speed_variation, yaw_variation);
      __driver.update(Driver::operationMode::OP_DRIVE, (int)speed_variation, (int)yaw_variation);
    }
  };
  
};

#endif /* DBCD007B_2AE4_4807_BE39_8D3ADAFADDB8 */

