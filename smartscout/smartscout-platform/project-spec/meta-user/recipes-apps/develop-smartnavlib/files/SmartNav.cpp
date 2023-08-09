#include "SmartNav.hpp"
#include <PositionEstimator.hpp>

#include <iostream>

#include <opencv2/core.hpp>
#include <PixelMagic.hpp>
#include <Ip.hpp>
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
  __tracker = Tracker::getInstance();
  // Create Reporter object
  __reporter = std::make_shared<Reporter>();
  // Create Driver instance 
  __driver = Driver::getInstance();
  // Create WebServer instance
  __web_server = WebServer::getInstance();
  // Create CaptureFrame instance
  __camera_capture = CaptureFrame::getInstance(img_width, img_height);
  // Create SmartEvasion
  __evader = SmartEvasion::getInstance();
  // Create a new thread
  __is_running.store(true);
  __working_mode.store(WorkingMode::DEFAULT);
  __show_camera.store(true);
  __navigation_thread = std::thread(&SmartNav::__navigation, this);
  DEBUG_PRINT("Smartnav created.\n");
}

SmartNav::~SmartNav() {
  DEBUG_PRINT("Smartnav destructor.\n");
  __is_running.store(false);
  __navigation_thread.join();
};

void SmartNav::__navigation() {
  int faults = 0;
  cv::Mat frame;
  FrameProcessor& frame_processor = FrameProcessor::getInstance();
  PositionEstimator& position_estimator = PositionEstimator::getInstance();

  // Set webserver callbacks
  __web_server->setSpeedCallback([]() {
    return Driver::getInstance()->getSpeed();
  }); 
  __web_server->setSmartLightsStatusCallback([this](bool lights_on) { 
    if (lights_on) 
      __headlights.update(90);
    else 
      __headlights.update(0);
  });
  __web_server->setWorkingModeCallback([this](WorkingMode working_mode) {
    __working_mode.store(working_mode);
  });
  __web_server->setShowCameraCallback([this](bool show_camera_data) {
    __show_camera.store(show_camera_data);
  });
  __web_server->setSmartEvasionStatusCallback([this](bool smart_evasion_status) {
    __evader->playSmartEvasion(smart_evasion_status);
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
  
  // RC control
  while(__is_running.load() && faults < 100) {
    auto start = std::chrono::high_resolution_clock::now();
    // Capture frame
    if (__show_camera.load())
      frame = __camera_capture->getFrame();
    else
      frame = __tracker->getMap();
      
    // Working mode
    switch (__working_mode.load()) {
    case WorkingMode::AUTOMATIC_EVASION:

      {
        CartesianPosition arrival_point(150, 0);
        __tracker->addTarget(position_estimator.relativizePoint(arrival_point));
        __working_mode.store(WorkingMode::DEFAULT);
      }

      break;
    case WorkingMode::SET_TARGET:
      // In progress...

      break;
    default: // Default working mode

      break;
    }
    // Draw recognized objects
    auto recognized_objects = frame_processor.getResults();
    if (!recognized_objects.empty()) {
      PixelMagic::drawBoundingBox(__imgTargetWidth, __imgTargetHeight, frame, recognized_objects);
    }
    // Send image to the remote app
    __camera_sender->send(frame);
    // Check if the target frame time was enough
    auto end = std::chrono::high_resolution_clock::now();  
    double elapsed = std::chrono::duration<double, std::milli>(end - start).count();  
    double remainingTime = __targetFrameTime - elapsed;
    if (remainingTime > 0) {
      if (faults > 0)
        faults--;
      std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<long long>(remainingTime)));
    }
    else 
      faults++;
	}
  std::cout << "While broken" << std::endl;
  __is_running.store(false);
  // Stop the car
  __driver->update(Driver::operationMode::OP_STOP, 0, 0);
  // Stop the WebServer
  __web_server->stop();
};