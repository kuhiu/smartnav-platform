#include "SmartNav.hpp"

#include <iostream>

#include <opencv2/core.hpp>
#include <PixelMagic.hpp>

#define DEBUG_SMARTNAV 1
#if defined(DEBUG_SMARTNAV) 
 	#define DEBUG_PRINT(fmt, args...) printf( "DEBUG: %s:%d:%s(): " fmt, \
																						__FILE__, __LINE__, __func__, ##args)
#else
	#define DEBUG_PRINT(fmt, args...) /* Don't do anything in release builds */
#endif

SmartNav::SmartNav(int img_width, int img_height, int img_framerate)
    : __imgTargetWidth(img_width), __imgTargetHeight(img_height), 
      __targetFrameTime(1.0 / img_framerate * 1000.0) {
  DEBUG_PRINT("Smartnav constructor.\n");
  // Create Frame sender object
  __camera_sender = std::make_shared<CameraSender>(img_width, img_height, img_framerate, std::string("10.0.0.20"), std::string("8080"));
  // Create Tracker object
  __tracker = std::make_shared<Tracker>();
  // Create Reporter object
  __reporter = std::make_shared<Reporter>(__tracker);
  // Create Driver instance 
  __driver = Driver::getInstance();
  // Create WebServer instance
  __web_server = WebServer::getInstance();
  // Create CaptureFrame instance
  __camera_capture = CaptureFrame::getInstance(img_width, img_height);
  // Create a new thread
  __is_running = true;
  __navigation_thread = std::thread(&SmartNav::__navigation, this);
  DEBUG_PRINT("Smartnav created.\n");
}

SmartNav::~SmartNav() {
  DEBUG_PRINT("Smartnav destructor.\n");
  __is_running = false;
  __navigation_thread.join();
};

void SmartNav::__navigation() {
  float curr_robot_angle;
  std::pair<float, float> pwm;
  CartesianPosition curr_position;
  // Relative target angle/position to the current angle/position
  float rel_direction_from_curr_angle;
  CartesianPosition rel_target_from_curr_pos;

  __web_server->setSpeedCallback([]() {
    return Driver::getInstance()->getSpeed();
  }); 
  __web_server->setSmartLightsStatusCallback([this](bool lights_on) { 
    this->__lights_on.store(lights_on); 
  });
  __web_server->setWorkingModeCallback([this](WorkingMode working_mode) {
    this->__working_mode = working_mode;
  });
  __web_server->setManualControlForwardCallback([](int pwm_delta) {
    Driver::getInstance()->update(Driver::operationMode::OP_DRIVE, pwm_delta, 0);
  }); 
  __web_server->setManualControlBackCallback([](int pwm_delta) {
    Driver::getInstance()->update(Driver::operationMode::OP_DRIVE, pwm_delta, 0);
  }); 
  __web_server->setManualControlLeftCallback([](int pwm_delta) {
    Driver::getInstance()->update(Driver::operationMode::OP_DRIVE, 0, pwm_delta);
  }); 
  __web_server->setManualControlRightCallback([](int pwm_delta) {
    Driver::getInstance()->update(Driver::operationMode::OP_DRIVE, 0, pwm_delta);
  }); 
  __web_server->setLeftDistanceSensorCallback([]() {
    return DistanceSensors::getInstance()->getDistances()[0];
  });
  __web_server->setCenterDistanceSensorCallback([]() {
    return DistanceSensors::getInstance()->getDistances()[1];
  });
  __web_server->setRightDistanceSensorCallback([]() {
    return DistanceSensors::getInstance()->getDistances()[2];
  });

  while(__is_running) {
    auto start = std::chrono::high_resolution_clock::now();
    // Capture frame
    cv::Mat frame = __camera_capture->getFrame();
/*  // Preprocessing image
    frame = PixelMagic::resize(frame, __imgTargetWidth, __imgTargetHeight);
		frame = PixelMagic::simpleWhiteBalance(frame);
    frame = PixelMagic::increaseSaturation(frame, 60);
    frame = PixelMagic::flip(frame, 1);
    frame = PixelMagic::flip(frame, 0); */
    // Lights control
    if (__lights_on.load()) {
      uint32_t light_lvl = PixelMagic::getBrightness(frame);
      std::cout << "Lights on: " << light_lvl << std::endl;
      __headlights.update(__smart_lights.evaluate(light_lvl));
    }
    else
      __headlights.update(0);
    // Get sensors distance
    std::vector<int> distances = DistanceSensors::getInstance()->getDistances();
    if (distances.size() != 3)
      throw std::runtime_error("Not three sensor outputs."); 
    // Working mode 
    switch (__working_mode) {
    case WorkingMode::AUTOMATIC_EVASION:
      {
        CartesianPosition arrival_point(100, 0);
        __tracker->addTarget(__position_estimator.relativizePoint(arrival_point));
        __working_mode = WorkingMode::REACH_TARGETS;
      }
      break;
    case WorkingMode::REACH_TARGETS:
      if (!__tracker->isTargetsEmpty()) {
/*         DEBUG_PRINT("__arrival_point x: %f, y: %f.\n", 
                    __tracker->getTargetToReach().x, 
                    __tracker->getTargetToReach().y); */
        // Get the current position of the robot
        curr_position = __position_estimator.getCurrentPosition();
        // Get the current angle of the robot
        curr_robot_angle = __position_estimator.getCurrentAngle();
        // Get the target position relative to the current position  
        rel_target_from_curr_pos = __tracker->getRelativeTargetPos(curr_position);
        // Get the target direction relative to the current angle
        rel_direction_from_curr_angle = __whereHaveToGo(rel_target_from_curr_pos);
        //auto time = std::chrono::system_clock::now();
        //Tracker::StepsTracker steps_tracker(  std::chrono::duration_cast<std::chrono::seconds>(time.time_since_epoch()).count(),
        //                                      curr_robot_angle,
        //                                      curr_position,
        //                                      rel_target_from_curr_pos);
        //__tracker->addStepsTracker(steps_tracker);
        // Target reached
        if (__tracker->targetReached(curr_position)) {
          __driver->update(Driver::operationMode::OP_STOP, 0, 0);
          continue; // Go to start of loop
        }
        // If one obstacle is ahead, stop and wait for the image detector response 
        if ((distances[1] < 75) && __obstacles.empty() ) {
          __visualization(curr_robot_angle, (float)distances[1], curr_position);
        }
        // Using SmartEvasion
        pwm = __evader.evade(curr_position, rel_target_from_curr_pos, 
            rel_direction_from_curr_angle, curr_robot_angle, __obstacles);
        // Motor control
        __driver->update_pwm((int)pwm.first, (int)pwm.second);
      }
      break;
    default: // Default working mode
      break;
    }
    // Send image to the remote app
    __camera_sender->send(frame);
    // Check if the target frame time was enough
		auto end = std::chrono::high_resolution_clock::now();  
    double elapsed = std::chrono::duration<double, std::milli>(end - start).count();  
    double remainingTime = __targetFrameTime - elapsed;
    if (remainingTime > 0) {
      std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long long>(remainingTime)));
    }
    else 
      throw std::runtime_error("The remaining time is less than zero.");
	}
  std::cout << "While broken" << std::endl;
  // Stop the car
  __driver->update(Driver::operationMode::OP_STOP, 0, 0);
  // Stop the WebServer
  __web_server->stop();
};
    
    // if (!__tracker->isTargetsEmpty()) {
    //   DEBUG_PRINT("__arrival_point x: %f, y: %f.\n", 
    //       __tracker->getTargetToReach().x, __tracker->getTargetToReach().y);
    //   curr_position = __position_estimator.getCurrentPosition();
    //   curr_robot_angle = __position_estimator.getCurrentAngle();
    //   rel_target_from_curr_pos = __getRelativeTargetPos(curr_position, __tracker->getTargetToReach());
    //   auto time = std::chrono::system_clock::now();
    //   Tracker::StepsTracker steps_tracker(  std::chrono::duration_cast<std::chrono::seconds>(time.time_since_epoch()).count(),
    //                                         curr_robot_angle,
    //                                         curr_position,
    //                                         rel_target_from_curr_pos);
    //   __tracker->addStepsTracker(steps_tracker);
    //   // Get the current direction where i've to go to reach my target
    //   curr_angle_to_target = __whereHaveToGo(rel_target_from_curr_pos);
    //   // Get sensors distance
    //   std::vector<int> distances = __distance_sensor.getDistances();
    //   if (distances.size() != 3)
    //     throw std::runtime_error("Not three sensor outputs."); 
    //   // Target reached
    //   if (__arrivation(curr_position, __tracker->getTargetToReach())) {
    //     __driver.update(Driver::operationMode::OP_STOP, 0, 0);
    //     __tracker->targetReached();
    //     continue; // Go to start of loop
    //   }
    //   // If one obstacle is ahead, stop and wait for the image detector response 
    //   if ((distances[1] < 75) && __obstacles.empty() ) {
    //     __visualization(curr_robot_angle, (float)distances[1], curr_position);
    //   }
    //   // Using SmartEvasion
    //   pwm = __evader.evade(curr_position, rel_target_from_curr_pos, 
    //       curr_angle_to_target, curr_robot_angle, __obstacles);
    //   // Motor control
    //   __driver.update_pwm((int)pwm.first, (int)pwm.second);
    //   // Debug
    //   DEBUG_PRINT("Brightness: %d.\n", (int)__capture_frame->getBrightness());
    //   DEBUG_PRINT("Distances: %d %d %d.\n", distances[0], distances[1], distances[2]);
    //   DEBUG_PRINT("pwm0 %f, pwm1 %f.\n", pwm.first, pwm.second);
    //   DEBUG_PRINT("curr_position x: %f, y: %f.\n", curr_position.x, curr_position.y);
    //   DEBUG_PRINT("Current target.x: %f, %f.\n", __tracker->getTargetToReach().x, __tracker->getTargetToReach().y);
    //   DEBUG_PRINT("curr_robot_angle: %f.\n", curr_robot_angle);
    //   DEBUG_PRINT("whereHaveToGo: %f.\n", curr_angle_to_target);
    // }
    // else
    //   std::this_thread::sleep_for(std::chrono::milliseconds(100));
  //}


void SmartNav::__visualization(float curr_robot_angle, float distance_to_obstacle, CartesianPosition curr_position) {
/*   bool object_found = false; 
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
  } */
}

/* void SmartNav::__frame_callback(std::shared_ptr<VirtualImage> img, void* ctx) {
  CaptureFrame* context = static_cast<CaptureFrame*> (ctx); 
  img->colorBalancing(1);
  img->increaseSaturation(60);
  img->flip(1);
  img->saveAsJpg("/home/root/test.jpg");
  if (context->getSaveFrameStatus()) {
    img->saveAsJpg("/home/root/object.jpg");
    context->setSaveFrame(false);
  }
  context->frame_processor.processFrame(img);
} */