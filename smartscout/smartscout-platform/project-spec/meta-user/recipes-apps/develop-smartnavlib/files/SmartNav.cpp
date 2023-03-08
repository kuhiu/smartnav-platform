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
  img->colorBalancing(0.5);
  img->increaseSaturation(50);
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
  float curr_angle;
  float speed_variation;
  float curr_angle_to_go;
  bool object_found = false; 
  std::vector<RecognitionResult> recognized_objects;
  std::vector<RecognitionResult> recognized_objects_saved;

  // Relativize the point to terrestrial north
  __arrival_point = __position_estimator.relativizePoint(__arrival_point); 
  DEBUG_PRINT("__arrival_point x: %f, y: %f.\n", __arrival_point.x, __arrival_point.y);
  while(__is_running) {
    // Estimate the current position
    CartesianPosition curr_position = __position_estimator.getCurrentPosition();    
    CartesianPosition curr_arrival_point = __getDestination(curr_position);
    // Get the current angle of the robot
    curr_angle = __position_estimator.getCurrentAngle();
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
      // Stop the robot
      __driver.update(Driver::operationMode::OP_STOP, 0, 0);
      // Get the results of the image processor 
      while(object_found == false) {
        __capture_frame->setSaveFrame(true);
        recognized_objects = __capture_frame->frame_processor.getResults();
        for (auto &result : recognized_objects) {
          DEBUG_PRINT("Label: %d.\n", result.label);
          if (result.label == 75) { // Waiting for the PC or TV detection
            object_found = true;
            recognized_objects_saved = recognized_objects;
            // Creating the obstacle
            PolarPosition obstacle_polar(curr_angle, (float)distances[1]);
            CartesianPosition obstacle_cartesian_pos = __position_estimator.polarToCartesian(obstacle_polar);
            obstacle_cartesian_pos.x = obstacle_cartesian_pos.x + curr_position.x;
            obstacle_cartesian_pos.y = obstacle_cartesian_pos.y + curr_position.y;
            // Width of the obstacle to avoid 
            // Leftmost point of the obstacle's width 
            PolarPosition leftmost_obstacle_point_pol((atan2((0.5-result.xmin)*16, (float)distances[1])*180/M_PI) + curr_angle, 
                (std::sqrt(std::pow(distances[1], 2) + std::pow((0.5-result.xmin)*16, 2))) );
            CartesianPosition leftmost_obstacle_point_cart = __position_estimator.polarToCartesian(leftmost_obstacle_point_pol);
            leftmost_obstacle_point_cart.x = leftmost_obstacle_point_cart.x + curr_position.x;
            leftmost_obstacle_point_cart.y = leftmost_obstacle_point_cart.y + curr_position.y;
            // Rightmost point of the obstacle's width 
            PolarPosition rightmost_obstacle_point_pol((atan2(-(result.xmax-0.5)*16, (float)distances[1])*180/M_PI) + curr_angle, 
                std::sqrt(std::pow(distances[1], 2) + std::pow((result.xmax-0.5)*16, 2)));
            CartesianPosition rightmost_obstacle_point_cart = __position_estimator.polarToCartesian(rightmost_obstacle_point_pol);
            rightmost_obstacle_point_cart.x = rightmost_obstacle_point_cart.x + curr_position.x;
            rightmost_obstacle_point_cart.y = rightmost_obstacle_point_cart.y + curr_position.y;
            // Create the obstacle
            Obstacle obstacle(obstacle_cartesian_pos, leftmost_obstacle_point_cart, rightmost_obstacle_point_cart);
            __obstacles.push_back(obstacle);
          }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
      }
    }
    DEBUG_PRINT("Brightness: %d.\n", (int)__capture_frame->getBrightness());
    DEBUG_PRINT("Distances: %d %d %d.\n", distances[0], distances[1], distances[2]);
    if (!__obstacles.empty()) {
      auto obstacle = __position_estimator.cartensianToPolar(__getObstaclePosition(curr_position));
      auto destination = __position_estimator.cartensianToPolar(curr_arrival_point);
      DEBUG_PRINT("obstacle.distance %f, destination.distance %f.\n", obstacle.distance, destination.distance);
      DEBUG_PRINT("obstacle.angle %f, destination.angle %f.\n", obstacle.angle, destination.angle);
      alpha = (obstacle.distance / destination.distance);
      theta = __getDifference(obstacle.angle, destination.angle);
    }
    else {
      alpha = 0;
      theta = 0;
    }
    DEBUG_PRINT("alpha %f, theta %f.\n", alpha, theta);
    std::vector<std::pair<std::string, float>> inputs = { {"alpha", alpha},
                                                          {"theta", theta}, 
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
      float obstacle_angle = __position_estimator.cartensianToPolar(__getObstaclePosition(curr_position)).angle;
      // Im looking go against the obstacle so..
      obstacle_angle = (obstacle_angle + 180.0);
      if (obstacle_angle > 180)
        obstacle_angle = obstacle_angle - 360; 
      DEBUG_PRINT("obstacle_angle %f.\n", obstacle_angle);
      yaw = w * obstacle_angle + (1-w) * curr_angle_to_go;
    }
    else {
      yaw = curr_angle_to_go;
    }
    float angle_diff = __getDifference(yaw, curr_angle);
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
      __angle_history.push_back(curr_angle);
      __arrival_point_history.push_back(curr_arrival_point);
      __timestamp.push_back(std::chrono::duration_cast<std::chrono::seconds>(time.time_since_epoch()).count());
    }      
    samples++;
    DEBUG_PRINT("curr_position x: %f, y: %f.\n", curr_position.x, curr_position.y);
    DEBUG_PRINT("curr_arrival_point.x: %f, curr_arrival_point.y: %f.\n", curr_arrival_point.x, curr_arrival_point.y);
    DEBUG_PRINT("curr_angle: %f.\n", curr_angle);
    DEBUG_PRINT("whereHaveToGo: %f.\n", curr_angle_to_go);
  }
  __driver.update(Driver::operationMode::OP_STOP, 0, 0);
  printf("Append to the history file.\n");
  __utilities.appedToFile(utilities::metadata(__position_history, __angle_history, __arrival_point_history,
          __timestamp, CartesianPosition(0.0, 0.0), __arrival_point, __obstacles, recognized_objects_saved));
};