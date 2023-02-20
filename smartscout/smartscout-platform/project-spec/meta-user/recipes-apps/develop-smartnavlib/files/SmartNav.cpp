#include "SmartNav.hpp"

#define DEBUG_SMARTNAV 1
#if defined(DEBUG_SMARTNAV) 
 	#define DEBUG_PRINT(fmt, args...) printf( "DEBUG: %s:%d:%s(): " fmt, \
																						__FILE__, __LINE__, __func__, ##args)
#else
	#define DEBUG_PRINT(fmt, args...) /* Don't do anything in release builds */
#endif

constexpr const char *SmartNav::__FUZZY_JSON;

SmartNav::SmartNav() {
  DEBUG_PRINT("Smartnav constructor.\n");
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
  DEBUG_PRINT("Smartnav created...\n");
}
/** Smartnav destructor */
SmartNav::~SmartNav() {
  DEBUG_PRINT("Smartnav destructor.\n");
  __driver.update(Driver::operationMode::OP_STOP, 0, 0);
  __is_running = false;
  __navigation_thread.join();
};

void SmartNav::__frame_callback(std::shared_ptr<VirtualImage> img, void* ctx) {
  CaptureFrame &context = *static_cast<CaptureFrame*> (ctx); 
  img->colorBalancing(1.0);
  img->saveAsJpg("/tmp/test.jpg");
  context.frame_processor.processFrame(img);
}

void SmartNav::__navigation() {
  float yaw_variation;
  float speed_variation;
  
  while(__is_running) {
    std::vector<int> distances = __distance_sensor.getDistances();
    // Check number of distances 
    if (distances.size() != 3)
      throw std::runtime_error("Not three sensor outputs.");
    DEBUG_PRINT("Compass mean: %f.\n", __compass.getValue());
    DEBUG_PRINT("Brightness: %d.\n", (int)__capture_frame->getBrightness());
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
    DEBUG_PRINT("Speed variation: %f. Yaw variation: %f.\n", speed_variation, yaw_variation);
    //__driver.update(Driver::operationMode::OP_DRIVE, (int)speed_variation, (int)yaw_variation);
  }
};