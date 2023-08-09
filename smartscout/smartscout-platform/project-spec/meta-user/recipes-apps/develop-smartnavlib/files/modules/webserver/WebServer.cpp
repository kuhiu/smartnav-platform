#include "WebServer.hpp"

#include <iostream>

#include <nlohmann/json.hpp>

WebServer *WebServer::__instance = nullptr;

WebServer *WebServer::getInstance() {
  if (__instance == nullptr) {
    __instance = new WebServer;
  }
  return __instance;
}

crow::json::wvalue WebServer::__get_speed_handler() {
  crow::json::wvalue ret;
  WebServer *web_server = getInstance();

  if (web_server->__speed_cb) {
    ret["speed"] = web_server->__speed_cb();
  }
  return ret;
};

crow::json::wvalue WebServer::__get_leftDistanceSensor_handler() {
  crow::json::wvalue ret;
  WebServer *web_server = getInstance();

  if (web_server->__leftDistanceSensor_cb) {
    ret["leftDistanceSensor"] = web_server->__leftDistanceSensor_cb();
  }
  return ret;
}

crow::json::wvalue WebServer::__get_centerDistanceSensor_handler() {
  crow::json::wvalue ret;
  WebServer *web_server = getInstance();

  if (web_server->__centerDistanceSensor_cb) {
    ret["centerDistanceSensor"] = web_server->__centerDistanceSensor_cb();
  }
  return ret;
}

crow::json::wvalue WebServer::__get_rightDistanceSensor_handler() {
  crow::json::wvalue ret;
  WebServer *web_server = getInstance();

  if (web_server->__rightDistanceSensor_cb) {
    ret["rightDistanceSensor"] = web_server->__rightDistanceSensor_cb();
  }
  return ret;
}

crow::response WebServer::__post_smartEvasion_status(const crow::request &req) {
  WebServer *web_server = getInstance();

  std::cout << "__post_smartEvasion_status" << std::endl;
  const std::string content_type = req.get_header_value("Content-Type");
  if (content_type == "application/json; charset=utf-8") {
    try {
      nlohmann::json data = nlohmann::json::parse(req.body);
      bool smartEvasionStatus_data = data["smartEvasionStatus"];
      std::cout << "smartEvasionStatus_data: " << smartEvasionStatus_data << std::endl;
      if (web_server->__smartEvasionStatus_cb) {
        web_server->__smartEvasionStatus_cb(smartEvasionStatus_data);
      }
      return crow::response(200);
    }
    catch (const std::exception &e) {
      return crow::response(400, e.what());
    }
  }
  return crow::response(400, "Invalid Content-Type. Expected application/json; charset=utf-8.");
}

crow::response WebServer::__post_smartEvasion_newTarget(const crow::request &req) {
  crow::json::wvalue ret;
  WebServer *web_server = getInstance();

  if (web_server->__smartEvasionNewTarget_cb) {
    ret["newTarget"] = web_server->__smartEvasionNewTarget_cb().toJson().dump();
  }
  return ret;
}

crow::response WebServer::__post_smartLights_status(const crow::request &req) {
  WebServer *web_server = getInstance();

  std::cout << "__post_smartLights_status" << std::endl;
  const std::string content_type = req.get_header_value("Content-Type");
  if (content_type == "application/json; charset=utf-8") {
    try {
      nlohmann::json data = nlohmann::json::parse(req.body);
      bool smartLightsStatus_data = data["smartLightsStatus"];
      std::cout << "smartLightsStatus_data: " << smartLightsStatus_data << std::endl;
      if (web_server->__smartLightStatus_cb) {
        web_server->__smartLightStatus_cb(smartLightsStatus_data);
      }
      return crow::response(200);
    }
    catch (const std::exception &e) {
      return crow::response(400, e.what());
    }
  }
  return crow::response(400, "Invalid Content-Type. Expected application/json; charset=utf-8.");
}

crow::response WebServer::__post_manualControlForward(const crow::request &req) {
  WebServer *web_server = getInstance();

  const std::string content_type = req.get_header_value("Content-Type");
  if (content_type == "application/json; charset=utf-8") {
    try {
      nlohmann::json data = nlohmann::json::parse(req.body);
      int manualControlForward_data = data["manualControlForward"];
      if (web_server->__manualControlForward_cb) {
        web_server->__manualControlForward_cb(manualControlForward_data);
      }
      return crow::response(200);
    }
    catch (const std::exception &e) {
      return crow::response(400, e.what());
    }
  }
  return crow::response(400, "Invalid Content-Type. Expected application/json; charset=utf-8.");
}

crow::response WebServer::__post_manualControlBack(const crow::request &req) {
  crow::json::wvalue ret;
  WebServer *web_server = getInstance();

  const std::string content_type = req.get_header_value("Content-Type");
  if (content_type == "application/json; charset=utf-8") {
    try {
      nlohmann::json data = nlohmann::json::parse(req.body);
      int manualControlBack_data = data["manualControlBack"];
      std::cout << "__post_manualControlBack: " << manualControlBack_data << std::endl;
      if (web_server->__manualControlBack_cb) {
        web_server->__manualControlBack_cb(manualControlBack_data);
      }
      return crow::response(200);
    }
    catch (const std::exception &e) {
      return crow::response(400, e.what());
    }
  }
  return crow::response(400, "Invalid Content-Type. Expected application/json; charset=utf-8.");
}

crow::response WebServer::__post_manualControlLeft(const crow::request &req) {
  crow::json::wvalue ret;
  WebServer *web_server = getInstance();
  
  const std::string content_type = req.get_header_value("Content-Type");
  if (content_type == "application/json; charset=utf-8") {
    try {
      nlohmann::json data = nlohmann::json::parse(req.body);
      int manualControlLeft_data = data["manualControlLeft"];
      if (web_server->__manualControlLeft_cb) {
        web_server->__manualControlLeft_cb(manualControlLeft_data);
      }
      return crow::response(200);
    }
    catch (const std::exception &e) {
      return crow::response(400, e.what());
    }
  }
  return crow::response(400, "Invalid Content-Type. Expected application/json; charset=utf-8.");
}

crow::response WebServer::__post_manualControlRight(const crow::request &req) {
  crow::json::wvalue ret;
  WebServer *web_server = getInstance();

  const std::string content_type = req.get_header_value("Content-Type");
  if (content_type == "application/json; charset=utf-8") {
    try {
      nlohmann::json data = nlohmann::json::parse(req.body);
      int manualControlRight_data = data["manualControlRight"];
      if (web_server->__manualControlRight_cb) {
        web_server->__manualControlRight_cb(manualControlRight_data);
      }
      return crow::response(200);
    }
    catch (const std::exception &e) {
      return crow::response(400, e.what());
    }
  }
  return crow::response(400, "Invalid Content-Type. Expected application/json; charset=utf-8.");
}

crow::response WebServer::__post_workingMode(const crow::request &req) {
  crow::json::wvalue ret;
  WebServer *web_server = getInstance();

  std::cout << "__post_workingMode" << std::endl;
  const std::string content_type = req.get_header_value("Content-Type");
  if (content_type == "application/json; charset=utf-8") {
    try {
      nlohmann::json data = nlohmann::json::parse(req.body);
      WorkingMode workingMode_data = data["workingMode"];
      std::cout << "workingMode_data: " << workingMode_data << std::endl;
      if (web_server->__workingMode_cb) {
        web_server->__workingMode_cb(workingMode_data);
      }
      return crow::response(200);
    }
    catch (const std::exception &e) {
      return crow::response(400, e.what());
    }
  }
  return crow::response(400, "Invalid Content-Type. Expected application/json; charset=utf-8.");
}

crow::response WebServer::__post_showCamera(const crow::request &req) {
  crow::json::wvalue ret;
  WebServer *web_server = getInstance();

  std::cout << "__post_showCamera" << std::endl;
  const std::string content_type = req.get_header_value("Content-Type");
  if (content_type == "application/json; charset=utf-8") {
    try {
      nlohmann::json data = nlohmann::json::parse(req.body);
      bool showCamera_data = data["showCamera"];
      std::cout << "showCamera_data: " << showCamera_data << std::endl;
      if (web_server->__showCamera_cb) {
        web_server->__showCamera_cb(showCamera_data);
      }
      return crow::response(200);
    }
    catch (const std::exception &e) {
      return crow::response(400, e.what());
    }
  }
  return crow::response(400, "Invalid Content-Type. Expected application/json; charset=utf-8.");
}