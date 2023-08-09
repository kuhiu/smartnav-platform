#ifndef A75E67F7_9C3F_4370_A541_4B1DB5BD2F02
#define A75E67F7_9C3F_4370_A541_4B1DB5BD2F02

#include <atomic>
#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

#include <CaptureFrame.hpp>
#include <Driver.hpp>
#include <DistanceSensors.hpp>
#include <FrameProcessor.hpp>
#include <FuzzyControlSystem.hpp>
#include <Headlights.hpp>
#include <DecayGraph.hpp>
#include <Obstacle.hpp>
#include <CartesionPosition.hpp>
#include <PolarPosition.hpp>
#include <Buttons.hpp>
#include <SmartEvasion.hpp>
#include <SmartLights.hpp>
#include <Tracker.hpp>
#include <Reporter.hpp>
#include <WebServer.hpp>
#include <PixelMagic.hpp>
#include <CameraSender.hpp>
#include <VdmaController.hpp>

class SmartNav {
public:
  /** Smartnav constructor */
  SmartNav(int img_width, int img_height, int img_framerate);
  /** Smartnav destructor */
  ~SmartNav();

private:
  /** Thread status */
  std::atomic<bool> __is_running;
  /** Target frame time */
  const double __targetFrameTime;
  /** Target image width */
  const int __imgTargetWidth;
  /** Target image height */
  const int __imgTargetHeight;
  /** VDMA controller */
  VdmaController __vdma;
  /** Working mode */
  std::atomic<WorkingMode> __working_mode;
  /** Show camera */
  std::atomic<bool> __show_camera;
  /** Thread navigation */
  std::thread __navigation_thread;
  /** Send the frame to the remote host */
  std::shared_ptr<CameraSender> __camera_sender;
  /** Headlights object */
  Headlights __headlights;
  /** CaptureFrame */
  CaptureFrame* __camera_capture;
  /** WebServer */
  WebServer* __web_server;
  /** Driver */
  Driver* __driver;
  /** Tracker object */
  Tracker* __tracker;
  /** Evasion object */
  SmartEvasion* __evader;
  /** Lights control */
  SmartLights __smart_lights;
  /** Reporter object */
  std::shared_ptr<Reporter> __reporter;
  /** Lights status */
  std::atomic<bool> __lights_on;
  /**
   * @brief Navigate
   * 
   */
  void __navigation();

};

#endif /* DBCD007B_2AE4_4807_BE39_8D3ADAFADDB8 */

