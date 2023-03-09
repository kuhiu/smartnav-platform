#include "SmartNav.hpp"

#define DEBUG_SMARTNAV 1
#if defined(DEBUG_SMARTNAV) 
 	#define DEBUG_PRINT(fmt, args...) printf( "DEBUG: %s:%d:%s(): " fmt, \
																						__FILE__, __LINE__, __func__, ##args)
#else
	#define DEBUG_PRINT(fmt, args...) /* Don't do anything in release builds */
#endif

constexpr const char *SmartNav::__FUZZY_JSON;

SmartNav::SmartNav(CartesianPosition arrival_point) 
    : __arrival_point(arrival_point) {
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

SmartNav::~SmartNav() {
  DEBUG_PRINT("Smartnav destructor.\n");
  __navigation_thread.join();
};

void SmartNav::__frame_callback(std::shared_ptr<VirtualImage> img, void* ctx) {
  CaptureFrame* context = static_cast<CaptureFrame*> (ctx); 
  img->colorBalancing(1);
  img->increaseSaturation(60);
  img->flip(1);
  if (context->getSaveFrameStatus()) {
    img->saveAsJpg("/tmp/test.jpg");
    context->setSaveFrame(false);
  }
  context->frame_processor.processFrame(img);
}

void SmartNav::__navigation() {
  float w = 0;
  float yaw;
  float alpha = 0;
  float theta = 0;
  int samples = 0;
  float curr_robot_angle;
  float speed_variation;
  float curr_angle_to_go;
  PolarPosition destination;
  CartesianPosition curr_position;
  CartesianPosition curr_arrival_point;
  PolarPosition closest_obstacle_point;
  PolarPosition furthest_obstacle_point;
  std::vector<RecognitionResult> recognized_objects;

  // Relativize the point to terrestrial north
  __arrival_point = __position_estimator.relativizePoint(__arrival_point); 
  DEBUG_PRINT("__arrival_point x: %f, y: %f.\n", __arrival_point.x, __arrival_point.y);
  while(__is_running) {
    // Estimate the current position
    curr_position = __position_estimator.getCurrentPosition();    
    curr_arrival_point = __getDestination(curr_position);
    // Get the current angle of the robot
    curr_robot_angle = __position_estimator.getCurrentAngle();
    // Get the current direction where i've to go to reach my target
    curr_angle_to_go = whereHaveToGo(curr_arrival_point);
    // Get sensors distance
    std::vector<int> distances = __distance_sensor.getDistances();
    if (distances.size() != 3)
      throw std::runtime_error("Not three sensor outputs.");
    // Check for collision or target arrivation 
    if (__arrivation(curr_position) || (distances[1] < 10)) 
      break;
    // If one obstacle is ahead, stop and wait for the image detector response 
    if ((distances[1] < 50) && (__obstacles.empty())) {
      recognized_objects = __visualization(curr_robot_angle, (float)distances[1], curr_position);
    }
    DEBUG_PRINT("Brightness: %d.\n", (int)__capture_frame->getBrightness());
    DEBUG_PRINT("Distances: %d %d %d.\n", distances[0], distances[1], distances[2]);
    // High values to reach target
    // if there are not obstacles
    alpha = 10;
    theta = 180;
    if (!__obstacles.empty()) {
      closest_obstacle_point = __getClosestObstaclePoint(curr_position, __obstacles[0]);
      furthest_obstacle_point = __getFurthestObstaclePoint(curr_position, __obstacles[0]);
      destination = __position_estimator.cartensianToPolar(curr_arrival_point);
      alpha = (closest_obstacle_point.distance / destination.distance);
      theta = __getDifference(furthest_obstacle_point.angle, destination.angle);
    }
    DEBUG_PRINT("alpha %f, theta %f.\n", alpha, theta);
    std::vector<std::pair<std::string, float>> inputs = { {"alpha", alpha},
                                                          {"theta", std::abs(theta)}, 
                                                          {"lighting", (float)__capture_frame->getBrightness()}  };
    // Evaluate fuzzy system
    auto outputs = __fuzzy_system->evaluate(inputs);
    // Read outputs 
    for (FuzzyOutput &output : outputs) {
      if (output.getName() == "w") 
        w = output.defuzzification();
      else if (output.getName() == "car_headlights")
        __headlights.update((uint32_t)output.defuzzification());
    }
    speed_variation = 5;
    if (!__obstacles.empty()) {
      // Im looking go against the obstacle so..
      furthest_obstacle_point.angle = (furthest_obstacle_point.angle + 180.0);
      if (furthest_obstacle_point.angle > 180)
        furthest_obstacle_point.angle = furthest_obstacle_point.angle - 360; 
      DEBUG_PRINT("obstacle_angle %f.\n", furthest_obstacle_point.angle);
      yaw = w * furthest_obstacle_point.angle + (1-w) * curr_angle_to_go;
    }
    else {
      yaw = curr_angle_to_go;
    }
    float angle_diff = __getDifference(yaw, curr_robot_angle);
    DEBUG_PRINT("angle_diff %f.\n", angle_diff);
    float yaw_pwm;
    if (angle_diff > 0)
      yaw_pwm = 10;
    else 
      yaw_pwm = -10;
    DEBUG_PRINT("Speed variation: %f. w: %f. yaw: %f.\n", speed_variation, w, yaw_pwm);
    __driver.update(Driver::operationMode::OP_DRIVE, (int)speed_variation, (int)yaw_pwm);
    
    if ((samples % 1) == 0) {
      // Save positions
      std::chrono::steady_clock::time_point time = std::chrono::steady_clock::now();
      DEBUG_PRINT("Save positions.\n");
      __position_history.push_back(curr_position);
      __angle_history.push_back(curr_robot_angle);
      __arrival_point_history.push_back(curr_arrival_point);
      __timestamp.push_back(std::chrono::duration_cast<std::chrono::seconds>(time.time_since_epoch()).count());
    }      
    samples++;
    DEBUG_PRINT("curr_position x: %f, y: %f.\n", curr_position.x, curr_position.y);
    DEBUG_PRINT("curr_arrival_point.x: %f, curr_arrival_point.y: %f.\n", curr_arrival_point.x, curr_arrival_point.y);
    DEBUG_PRINT("curr_robot_angle: %f.\n", curr_robot_angle);
    DEBUG_PRINT("whereHaveToGo: %f.\n", curr_angle_to_go);
  }
  __driver.update(Driver::operationMode::OP_STOP, 0, 0);
  printf("Append to the history file.\n");
  __utilities.appedToFile(utilities::metadata(__position_history, __angle_history, __arrival_point_history,
          __timestamp, CartesianPosition(0.0, 0.0), __arrival_point, __obstacles, recognized_objects));
};

std::vector<RecognitionResult> SmartNav::__visualization(float curr_robot_angle, float distance_to_obstacle, CartesianPosition curr_position) {
  bool object_found = false; 
  std::vector<RecognitionResult> recognized_objects;
  std::vector<RecognitionResult> recognized_objects_saved;
  // Stop the robot
  __driver.update(Driver::operationMode::OP_STOP, 0, 0);
  // Get the results of the image processor 
  while(object_found == false) {
    recognized_objects = __capture_frame->frame_processor.getResults();
    for (auto &recognized_object : recognized_objects) {
      DEBUG_PRINT("Label: %d.\n", recognized_object.label);
      if (recognized_object.label == 75) { // Waiting for the specific class to detect
        // Save the next frame
        __capture_frame->setSaveFrame(true);
        // The object was found, save the CNN outputs
        object_found = true;
        recognized_objects_saved = recognized_objects;
        // Create the obstacle
        Obstacle obstacle(curr_robot_angle, distance_to_obstacle, curr_position, recognized_object);
        __obstacles.push_back(obstacle);
      }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  return recognized_objects_saved;
}