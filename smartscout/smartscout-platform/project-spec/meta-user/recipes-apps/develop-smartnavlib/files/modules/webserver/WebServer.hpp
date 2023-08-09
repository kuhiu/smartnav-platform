#ifndef F308890A_6D92_492A_9A0B_999AA4E16162
#define F308890A_6D92_492A_9A0B_999AA4E16162

#include <stdio.h>

#include "crow.h"
#include <crow/http_request.h>

#include <atomic>
#include <functional>
#include <thread>

#include <CartesionPosition.hpp>
#include <WorkingMode.hpp>

class WebServer {
public:
  /** Speed callback */
  using SpeedCallback = std::function<int()>;
  /** Headlight callback */
  using DistanceSensorCallback = std::function<int()>;
  /** SmartEvasionStatus callback */
  using SmartEvasionStatusCallback = std::function<void(bool)>;
  /** SmartEvasionNewTarget callback*/
  using SmartEvasionNewTargetCallback = std::function<CartesianPosition()>;
  /** SmartLightsStatus callback */
  using SmartLightsStatusCallback = std::function<void(bool)>;
  /** ManualControl callback */
  using ManualControlCallback = std::function<void(int)>;
  /** WorkingMode callback */
  using WorkingModeCallback = std::function<void(WorkingMode)>;
  /** showCamera callback */
  using ShowCameraCallback = std::function<void(bool)>;
  /**
   * @brief Get the Instance of the WebServer
   * 
   * @return WebServer* 
   */
  static WebServer* getInstance();
  /**
   * @brief Stop the webserver.
   * 
   */
  void stop() {
    __webServer.stop();
    __web_server_thread.join();
    std::cout << "WebServer stopped." << std::endl;
  }
  /**
   * @brief Deleting copy constructor
   * 
   * @param obj 
   */
  WebServer(const WebServer& obj) = delete;
  /**
   * @brief Singleton should not be assignable
   * 
   */
  void operator=(const WebServer&) = delete;
  /**
   * @brief Set the Speed Callback 
   * 
   * @param speed_cb 
   */
  void setSpeedCallback(SpeedCallback speed_cb) {
    __speed_cb = speed_cb;
  }
  /**
   * @brief Set the LeftDistanceSensor Callback
   * 
   * @param leftDistanceSensor_cb 
   */
  void setLeftDistanceSensorCallback(DistanceSensorCallback leftDistanceSensor_cb) {
    __leftDistanceSensor_cb = leftDistanceSensor_cb;
  }
  /**
   * @brief Set the RightDistanceSensor Callback
   * 
   * @param rightDistanceSensor_cb 
   */
  void setRightDistanceSensorCallback(DistanceSensorCallback rightDistanceSensor_cb) {
    __rightDistanceSensor_cb = rightDistanceSensor_cb;
  }
  /**
   * @brief Set the CenterDistanceSensor Callback
   * 
   * @param centerDistanceSensor_cb 
   */
  void setCenterDistanceSensorCallback(DistanceSensorCallback centerDistanceSensor_cb) {
    __centerDistanceSensor_cb = centerDistanceSensor_cb;
  }
  /**
   * @brief Set the SmartEvasionStatus Callback
   * 
   * @param smartEvasionStatus_cb 
   */
  void setSmartEvasionStatusCallback(SmartEvasionStatusCallback smartEvasionStatus_cb) {
    __smartEvasionStatus_cb = smartEvasionStatus_cb;
  }
  /**
   * @brief Set the SmartEvasionNewTarget Callback
   * 
   * @param smartEvasionNewTarget_cb 
   */
  void setSmartEvasionNewTargetCallback(SmartEvasionNewTargetCallback smartEvasionNewTarget_cb) {
    __smartEvasionNewTarget_cb = smartEvasionNewTarget_cb;
  }
  /**
   * @brief Set the SmartLightsStatus Callback
   * 
   * @param smartLightsStatus_cb 
   */
  void setSmartLightsStatusCallback(SmartLightsStatusCallback smartLightsStatus_cb) {
    __smartLightStatus_cb = smartLightsStatus_cb;
  }
  /**
   * @brief Set the ManualControlForward Callback 
   * 
   * @param manualControlForward_cb 
   */
  void setManualControlForwardCallback(ManualControlCallback manualControlForward_cb) {
    __manualControlForward_cb = manualControlForward_cb; 
  }
  /**
   * @brief Set the ManualControlBack Callback
   * 
   * @param manualControlBack_cb 
   */
  void setManualControlBackCallback(ManualControlCallback manualControlBack_cb) {
    __manualControlBack_cb = manualControlBack_cb; 
  }
  /**
   * @brief Set the ManualControlLeft Callback
   * 
   * @param manualControlLeft_cb 
   */
  void setManualControlLeftCallback(ManualControlCallback manualControlLeft_cb) {
    __manualControlLeft_cb = manualControlLeft_cb; 
  }
  /**
   * @brief Set the ManualControlRight Callback
   * 
   * @param manualControlRight_cb 
   */
  void setManualControlRightCallback(ManualControlCallback manualControlRight_cb) {
    __manualControlRight_cb = manualControlRight_cb; 
  }
  /**
   * @brief Set the Working Mode Callback
   * 
   * @param workingMode_cb 
   */
  void setWorkingModeCallback(WorkingModeCallback workingMode_cb) {
    __workingMode_cb = workingMode_cb;
  }
  /**
   * @brief Set the show camera Mode Callback
   * 
   * @param showCamera_cb 
   */
  void setShowCameraCallback(ShowCameraCallback showCamera_cb) {
    __showCamera_cb = showCamera_cb;
  }

  private:
    /** Singleton instance */
    static WebServer* __instance;
    /** Webserver port */
    const int __PORT = 18080;
    /** Thread */
    std::thread __web_server_thread;
    /** WebServer object */
    crow::SimpleApp __webServer;
    /** WebServer constructor */
    WebServer() {
      __setEndopoints();
      __web_server_thread = std::thread(&WebServer::__running, this);
    };
    /** WebServer destructor */
    ~WebServer() {
      __web_server_thread.join();
    };
    /** Callbacks for realtime variables */
    SpeedCallback __speed_cb;
    DistanceSensorCallback __leftDistanceSensor_cb;
    DistanceSensorCallback __centerDistanceSensor_cb;
    DistanceSensorCallback __rightDistanceSensor_cb;
    SmartEvasionStatusCallback __smartEvasionStatus_cb;
    SmartEvasionNewTargetCallback __smartEvasionNewTarget_cb;
    SmartLightsStatusCallback __smartLightStatus_cb;
    ManualControlCallback __manualControlForward_cb;
    ManualControlCallback __manualControlBack_cb;
    ManualControlCallback __manualControlLeft_cb;
    ManualControlCallback __manualControlRight_cb;
    WorkingModeCallback __workingMode_cb;
    ShowCameraCallback __showCamera_cb;
    /**
     * @brief Set the webserver endpoints
     * 
     */
    void __setEndopoints() {
      // GET request
      CROW_ROUTE(__webServer, "/").methods(crow::HTTPMethod::GET)(&__get_root_handler);
      CROW_ROUTE(__webServer, "/api/realtime/variables/speed").methods(crow::HTTPMethod::GET)(&__get_speed_handler);
      CROW_ROUTE(__webServer, "/api/realtime/variables/leftDistanceSensor").methods(crow::HTTPMethod::GET)(&__get_leftDistanceSensor_handler);
      CROW_ROUTE(__webServer, "/api/realtime/variables/centerDistanceSensor").methods(crow::HTTPMethod::GET)(&__get_centerDistanceSensor_handler);
      CROW_ROUTE(__webServer, "/api/realtime/variables/rightDistanceSensor").methods(crow::HTTPMethod::GET)(&__get_rightDistanceSensor_handler);
      // POST request
      CROW_ROUTE(__webServer, "/api/realtime/variables/showCamera").methods(crow::HTTPMethod::POST)(&__post_showCamera);
      CROW_ROUTE(__webServer, "/api/realtime/variables/workingMode").methods(crow::HTTPMethod::POST)(&__post_workingMode);
      CROW_ROUTE(__webServer, "/api/realtime/variables/workingMode/smartEvasion/status").methods(crow::HTTPMethod::POST)(&__post_smartEvasion_status);
      CROW_ROUTE(__webServer, "/api/realtime/variables/workingMode/smartEvasion/newTarget").methods(crow::HTTPMethod::POST)(&__post_smartEvasion_newTarget);
      CROW_ROUTE(__webServer, "/api/realtime/variables/smartLights/status").methods(crow::HTTPMethod::POST)(&__post_smartLights_status);
      CROW_ROUTE(__webServer, "/api/realtime/variables/manualControlForward").methods(crow::HTTPMethod::POST)(&__post_manualControlForward);
      CROW_ROUTE(__webServer, "/api/realtime/variables/manualControlBack").methods(crow::HTTPMethod::POST)(&__post_manualControlBack);
      CROW_ROUTE(__webServer, "/api/realtime/variables/manualControlLeft").methods(crow::HTTPMethod::POST)(&__post_manualControlLeft);
      CROW_ROUTE(__webServer, "/api/realtime/variables/manualControlRight").methods(crow::HTTPMethod::POST)(&__post_manualControlRight);
  
    };
    /**
     * @brief Start the web server
     * 
     * @param port 
     */
    void __running() {
      // ignore all log
      __webServer.loglevel(crow::LogLevel::Warning);
      __webServer.port(__PORT)
                .server_name("SmartNavWebServer")
                .run();
    }    
    /**
     * @brief Get method of the root handler
     * 
     * @return crow::mustache::rendered_template 
     */
    static crow::mustache::rendered_template __get_root_handler() {
      // Set templates directory
      crow::mustache::set_base("/etc/webserver/templates");
      return crow::mustache::load("index.html").render();
    };
    /**
     * @brief Get method of the speed real-time variable
     * 
     * @return crow::json::wvalue 
     */
    static crow::json::wvalue __get_speed_handler();
    /**
     * @brief Get method of the leftDistanceSensor real-time variable
     * 
     * @return crow::json::wvalue 
     */
    static crow::json::wvalue __get_leftDistanceSensor_handler();
    /**
     * @brief Get method of the centerDistanceSensor real-time variable
     * 
     * @return crow::json::wvalue 
     */
    static crow::json::wvalue __get_centerDistanceSensor_handler();
    /**
     * @brief Get method of the centerDistanceSensor real-time variable
     * 
     * @return crow::json::wvalue 
     */
    static crow::json::wvalue __get_rightDistanceSensor_handler();
    /**
     * @brief Post method of the smartEvasion Status real-time variable
     * 
     * @param req 
     * @return crow::response 
     */
    static crow::response __post_smartEvasion_status(const crow::request& req);
    /**
     * @brief Post method of the smartEvasion NewTarget real-time variable
     * 
     * @param req 
     * @return crow::response 
     */
    static crow::response __post_smartEvasion_newTarget(const crow::request& req);
    /**
     * @brief Post method of the smartLights real-time variable
     * 
     * @param req 
     * @return crow::response 
     */
    static crow::response __post_smartLights_status(const crow::request& req);
    /**
     * @brief Post method of the manualControlForward real-time variable
     * 
     * @param req 
     * @return crow::response 
     */
    static crow::response __post_manualControlForward(const crow::request& req);
    /**
     * @brief Post method of the manualControlBack real-time variable
     * 
     * @param req 
     * @return crow::response 
     */
    static crow::response __post_manualControlBack(const crow::request& req);
    /**
     * @brief Post method of the manualControlLeft real-time variable
     * 
     * @param req 
     * @return crow::response 
     */
    static crow::response __post_manualControlLeft(const crow::request& req);
    /**
     * @brief Post method of the manualControlRigth real-time variable
     * 
     * @param req 
     * @return crow::response 
     */
    static crow::response __post_manualControlRight(const crow::request& req);
    /**
     * @brief Post method of the Working mode real-time variable
     * 
     * @param req 
     * @return crow::response 
     */
    static crow::response __post_workingMode(const crow::request& req);
    /**
     * @brief Post method of the showCamera real-time variable
     * 
     * @param req 
     * @return crow::response 
     */
    static crow::response __post_showCamera(const crow::request& req);

};

#endif /* F308890A_6D92_492A_9A0B_999AA4E16162 */
