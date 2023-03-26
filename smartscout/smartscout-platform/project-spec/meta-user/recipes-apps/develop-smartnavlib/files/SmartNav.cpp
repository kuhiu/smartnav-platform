#include "SmartNav.hpp"

#define DEBUG_SMARTNAV 1
#if defined(DEBUG_SMARTNAV) 
 	#define DEBUG_PRINT(fmt, args...) printf( "DEBUG: %s:%d:%s(): " fmt, \
																						__FILE__, __LINE__, __func__, ##args)
#else
	#define DEBUG_PRINT(fmt, args...) /* Don't do anything in release builds */
#endif

SmartNav::SmartNav() {
  DEBUG_PRINT("Smartnav constructor.\n");
  // Create Capture frame object
  __capture_frame = std::make_shared<CaptureFrame>(__frame_callback, 640, 480, CaptureFrame::pixelFormat::PIX_FMT_RGB24, 1);
  // Create Tracker object
  __tracker = std::make_shared<Tracker>();
  // Create Reporter object
  __reporter = std::make_shared<Reporter>(__tracker);
  // Create a new thread
  __is_running = true;
  __navigation_thread = std::thread(&SmartNav::__navigation, this);
  DEBUG_PRINT("Smartnav created...\n");
}

SmartNav::~SmartNav() {
  DEBUG_PRINT("Smartnav destructor.\n");
  __is_running = false;
  __navigation_thread.join();
};

void SmartNav::__frame_callback(std::shared_ptr<VirtualImage> img, void* ctx) {
  CaptureFrame* context = static_cast<CaptureFrame*> (ctx); 
  img->colorBalancing(1);
  img->increaseSaturation(60);
  img->flip(1);
  if (context->getSaveFrameStatus()) {
    img->saveAsJpg("/home/root/test.jpg");
    context->setSaveFrame(false);
  }
  context->frame_processor.processFrame(img);
}

void SmartNav::__navigation() {
  float curr_angle_to_target;
  float curr_robot_angle;
  std::pair<float, float> pwm;
  CartesianPosition curr_position;
  // Relative target position to the current position
  CartesianPosition rel_target_from_curr_pos;

  while(__is_running) {
    // Lights control
    __headlights.update(__smart_lights.evaluate((float)__capture_frame->getBrightness()));
    
    if (!__tracker->isTargetsEmpty()) {
      DEBUG_PRINT("__arrival_point x: %f, y: %f.\n", 
          __tracker->getTargetToReach().x, __tracker->getTargetToReach().y);
      curr_position = __position_estimator.getCurrentPosition();
      curr_robot_angle = __position_estimator.getCurrentAngle();
      rel_target_from_curr_pos = __getRelativeTargetPos(curr_position, __tracker->getTargetToReach());
      auto time = std::chrono::system_clock::now();
      Tracker::StepsTracker steps_tracker(  std::chrono::duration_cast<std::chrono::seconds>(time.time_since_epoch()).count(),
                                            curr_robot_angle,
                                            curr_position,
                                            rel_target_from_curr_pos);
      __tracker->addStepsTracker(steps_tracker);
      // Get the current direction where i've to go to reach my target
      curr_angle_to_target = __whereHaveToGo(rel_target_from_curr_pos);
      // Get sensors distance
      std::vector<int> distances = __distance_sensor.getDistances();
      if (distances.size() != 3)
        throw std::runtime_error("Not three sensor outputs."); 
      // Target reached
      if (__arrivation(curr_position, __tracker->getTargetToReach())) {
        __driver.update(Driver::operationMode::OP_STOP, 0, 0);
        __tracker->targetReached();
        continue; // Go to start of loop
      }
      // If one obstacle is ahead, stop and wait for the image detector response 
      if (distances[1] < 50) {
        __visualization(curr_robot_angle, (float)distances[1], curr_position);
      }
      // Using SmartEvasion
      pwm = __evader.evade(curr_position, rel_target_from_curr_pos, 
          curr_angle_to_target, curr_robot_angle, __obstacles);
      // Motor control
      __driver.update_pwm((int)pwm.first, (int)pwm.second);
      // Debug
      DEBUG_PRINT("Brightness: %d.\n", (int)__capture_frame->getBrightness());
      DEBUG_PRINT("Distances: %d %d %d.\n", distances[0], distances[1], distances[2]);
      DEBUG_PRINT("pwm0 %f, pwm1 %f.\n", pwm.first, pwm.second);
      DEBUG_PRINT("curr_position x: %f, y: %f.\n", curr_position.x, curr_position.y);
      DEBUG_PRINT("Current target.x: %f, %f.\n", __tracker->getTargetToReach().x, __tracker->getTargetToReach().y);
      DEBUG_PRINT("curr_robot_angle: %f.\n", curr_robot_angle);
      DEBUG_PRINT("whereHaveToGo: %f.\n", curr_angle_to_target);
    }
    else
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  __driver.update(Driver::operationMode::OP_STOP, 0, 0);
};

void SmartNav::__visualization(float curr_robot_angle, float distance_to_obstacle, CartesianPosition curr_position) {
  bool object_found = false; 
  std::vector<RecognitionResult> recognized_objects;
  // Stop the robot
  __driver.update(Driver::operationMode::OP_STOP, 0, 0);
  // Get the results of the image processor 
  while(object_found == false && __is_running) {
    recognized_objects = __capture_frame->frame_processor.getResults();
    for (auto &recognized_object : recognized_objects) {
      DEBUG_PRINT("Label: %d.\n", recognized_object.label);
      if ((recognized_object.label == 75) || (recognized_object.label == 76)) { // Waiting for the specific class to detect
        // Save the next frame
        __capture_frame->setSaveFrame(true);
        // The object was found, save the CNN outputs
        object_found = true;  
        // Add the recognized object to the tracker
        __tracker->addRecognizedObject(recognized_object);
        // Create the obstacle
        Obstacle obstacle(curr_robot_angle, distance_to_obstacle, curr_position, recognized_object);
        __obstacles.push_back(obstacle);
      }
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}