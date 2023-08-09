#include <SmartEvasion.hpp>

#include <chrono>

#include <CaptureFrame.hpp>
#include <DistanceSensors.hpp>
#include <Driver.hpp>
#include <Tracker.hpp>
#include <PixelMagic.hpp>

constexpr const char *SmartEvasion::__FUZZY_S1_JSON;
constexpr const char *SmartEvasion::__FUZZY_S2_JSON;

#define DEBUG_SMARTEVASION 1
#if defined(DEBUG_SMARTEVASION) 
 	#define DEBUG_PRINT(fmt, args...) printf( "DEBUG: %s:%d:%s(): " fmt, \
																						__FILE__, __LINE__, __func__, ##args)
#else
	#define DEBUG_PRINT(fmt, args...) /* Don't do anything in release builds */
#endif

SmartEvasion *SmartEvasion::__instance = nullptr;

SmartEvasion *SmartEvasion::getInstance() {
  if (__instance == nullptr) {
    __instance = new SmartEvasion;
  }
  return __instance;
}

SmartEvasion::SmartEvasion() {
  DEBUG_PRINT("SmartEvasion constructor.\n");
  // Parse fuzzy system file 
  std::ifstream fuzzy_system_s1_file(__FUZZY_S1_JSON);
  const json fuzzy_system_s1_json = json::parse(fuzzy_system_s1_file);
  std::ifstream fuzzy_system_s2_file(__FUZZY_S2_JSON);
  const json fuzzy_system_s2_json = json::parse(fuzzy_system_s2_file);
  // Create fuzzy control system object
  __fuzzy_system_stage_1 = std::make_shared<FuzzyControlSystem>(FuzzyControlSystem::parse(fuzzy_system_s1_json));
  __fuzzy_system_stage_2 = std::make_shared<FuzzyControlSystem>(FuzzyControlSystem::parse(fuzzy_system_s2_json));
  // Start thread
  __is_running.store(true);
  __evasion_thread = std::thread(&SmartEvasion::__waitNewTarget, this);
  DEBUG_PRINT("SmartEvasion created.\n");
};

void SmartEvasion::__waitNewTarget() {
  float curr_robot_angle;
  std::pair<float, float> pwm;
  CartesianPosition curr_position;
  Tracker* tracker = Tracker::getInstance();
  PositionEstimator& position_estimator = PositionEstimator::getInstance();
  Driver* driver = Driver::getInstance();
  FrameProcessor& frame_processor = FrameProcessor::getInstance();

  while (__is_running.load()) {
    if (!tracker->isTargetsEmpty()) {
      // Get sensors distance
      std::vector<int> distances = DistanceSensors::getInstance()->getDistances();
      if (distances.size() != 3)
        throw std::runtime_error("Not three sensor outputs."); 
      // Get the current position of the robot
      curr_position = position_estimator.getCurrentPosition();
      // Get the current angle of the robot
      curr_robot_angle = position_estimator.getCurrentAngle();
      // Create an step tracker
      auto time = std::chrono::system_clock::now();
      Tracker::StepsTracker step_tracker(std::chrono::duration_cast<std::chrono::seconds>(time.time_since_epoch()).count(),
        curr_robot_angle,
        curr_position);
      tracker->updateMap(step_tracker);
      // Target reached
      if (tracker->targetReached(curr_position)) {
        // Stop the rc car
        driver->update(Driver::operationMode::OP_STOP, 0, 0);
        __obstacles.clear();
      }
      else {
        // If one obstacle is ahead, stop and wait for the image detector response 
        if ((distances[1] < 75) && __obstacles.empty() ) {
          DEBUG_PRINT("New obstacle to avoid.\n");
          // Stop the robot
          driver->update(Driver::operationMode::OP_STOP, 0, 0);
          // Sleep a while
          std::this_thread::sleep_for(std::chrono::milliseconds(300));
          // Process frame
          auto frame = CaptureFrame::getInstance(320, 240)->getFrame();
          frame_processor.processFrame(frame);
          auto recognized_objects = frame_processor.getResults();
          if (!recognized_objects.empty()) {
            DEBUG_PRINT("New obstacle recognized.\n");
            // Get dimensions of the obstacle
            __obstacleDimensionExtractor(recognized_objects, curr_robot_angle, (float)distances[1], curr_position);
          }
          else {
            DEBUG_PRINT("The obstacle was not recognized.\n");
            tracker->deleteTarget();
            continue;
          }
        }
        // Wait play
        DEBUG_PRINT("Wait play.\n");
        while (!__play_smart_evasion.load()) {
          // Stop the robot
          driver->update(Driver::operationMode::OP_STOP, 0, 0);
          std::this_thread::sleep_for(std::chrono::milliseconds(200)); 
        }
        DEBUG_PRINT("Play arrived.\n");
        frame_processor.clearResults();
        // Using SmartEvasion
        pwm = __evade(curr_position, curr_robot_angle, __obstacles);
        // Motor control
        driver->update_pwm((int)pwm.first, (int)pwm.second);
        // Debug
        DEBUG_PRINT("pwm0 %f, pwm1 %f.\n", pwm.first, pwm.second);
        DEBUG_PRINT("curr_position: %f, %f.\n", curr_position.x, curr_position.y);
        DEBUG_PRINT("Current target: %f, %f.\n", tracker->getTargetToReach().x, tracker->getTargetToReach().y);
        DEBUG_PRINT("curr_robot_angle: %f.\n", curr_robot_angle);
      }
    }
    else {
      std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
  }
}

void SmartEvasion::__obstacleDimensionExtractor(std::vector<RecognitionResult> recognized_objects, 
        float curr_robot_angle, float distance_to_obstacle, CartesianPosition curr_position) {
  bool object_found = false; 

  for (auto &recognized_object : recognized_objects) {
    // Create the obstacle
    Obstacle obstacle(curr_robot_angle, distance_to_obstacle, curr_position, recognized_object);
    __obstacles.push_back(obstacle);
    DEBUG_PRINT("Obstacle position: %f, %f.\n", obstacle.getPosition().x, obstacle.getPosition().y);
    DEBUG_PRINT("Obstacle left position: %f, %f.\n", obstacle.getLeftmostPoint().x, obstacle.getLeftmostPoint().y);
    DEBUG_PRINT("Obstacle right positionn: %f, %f.\n", obstacle.getRightmostPoint().x, obstacle.getRightmostPoint().y);
    // Get the obstacle points 
    const CartesianPosition closest_obstacle = __obstacles[0].getClosestPoint();
    const CartesianPosition furthest_obstacle = __obstacles[0].getFurthestPoint();
    // Test
    const PolarPosition closest_obstacle_pol = PositionEstimator::cartensianToPolar(closest_obstacle);
    const PolarPosition furthest_obstacle_pol = PositionEstimator::cartensianToPolar(furthest_obstacle);
    DEBUG_PRINT("(0,0) closest_obstacle_point %f y %f.\n", closest_obstacle_pol.distance, closest_obstacle_pol.angle);
    DEBUG_PRINT("(0,0) furthest_obstacle_point %f y %f.\n", furthest_obstacle_pol.distance, furthest_obstacle_pol.angle);
  }
  DEBUG_PRINT("End dimension extractor.\n");
}

std::pair<float, float> SmartEvasion::__evade(CartesianPosition curr_position, float curr_robot_angle, std::vector<Obstacle> obstacles) {
  float w = 0;
  float alpha = 0;
  float theta = 0;
  float target_distance;
  float angle_correction;
  float target_direction_angle;
  float closest_obstacle_distance;
  float furthest_obstacle_angle;
  std::pair<float, float> ret; 
  float current_destination_angle;
  std::vector<FuzzyOutput> outputs;
  CartesianPosition target_direction;
  CartesianPosition evader_direction; 
  CartesianPosition current_destination;
  Tracker* tracker = Tracker::getInstance();
  std::vector<std::pair<std::string, float>> inputs;
  // Get the target point
  const CartesianPosition target = tracker->getTargetToReach();
  // Get the obstacle points 
  const CartesianPosition closest_obstacle = obstacles[0].getClosestPoint();
  const CartesianPosition furthest_obstacle = obstacles[0].getFurthestPoint();

  target_direction = target - curr_position;
  target_direction_angle = PositionEstimator::cartensianToPolar(target_direction).angle;
  // If there are not obstacles
  if (!obstacles.empty()) {
    target_distance = PositionEstimator::cartensianToPolar(target - curr_position).distance;
    closest_obstacle_distance = PositionEstimator::cartensianToPolar(closest_obstacle - curr_position).distance;
    furthest_obstacle_angle = PositionEstimator::cartensianToPolar(furthest_obstacle - curr_position).angle;

    alpha = (closest_obstacle_distance / target_distance);
    theta = __subtractAngles(furthest_obstacle_angle, target_direction_angle);
    DEBUG_PRINT("alpha %f, theta %f.\n", alpha, theta);
    // Fuzzy control system: Stage 1 
    inputs = {  {"alpha", alpha},
                {"theta", std::abs(theta)} };
    // Evaluate fuzzy system
    outputs = __fuzzy_system_stage_1->evaluate(inputs);
    // Read outputs 
    for (FuzzyOutput &output : outputs) {
      if (output.getName() == "w") 
        w = output.defuzzification();
    }  
    // Im looking go against the obstacle so..
    evader_direction = __supplementary(furthest_obstacle - curr_position);
    DEBUG_PRINT("evader_direction angle %f.\n", PositionEstimator::cartensianToPolar(evader_direction).angle);
    current_destination = __scalarVectorMult(evader_direction, w) + __scalarVectorMult(target_direction, (1-w));
    current_destination_angle = PositionEstimator::cartensianToPolar(current_destination).angle;
  }
  else 
    current_destination_angle = target_direction_angle;

  angle_correction = __subtractAngles(curr_robot_angle, current_destination_angle);
  // Fuzzy control system: Stage 2 
  inputs = { {"where_have_to_go", angle_correction} };
  // Evaluate fuzzy system
  outputs = __fuzzy_system_stage_2->evaluate(inputs);
  // Read outputs 
  for (FuzzyOutput &output : outputs) {
    if (output.getName() == "pwm0") 
      ret.first = output.defuzzification();
    else if (output.getName() == "pwm1")
      ret.second = output.defuzzification();
  }
  DEBUG_PRINT("closest_obstacle_distance %f.\n", closest_obstacle_distance);
  DEBUG_PRINT("furthest_obstacle_angle %f.\n", furthest_obstacle_angle);
  DEBUG_PRINT("furthest_obstacle - current position x,y %f,%f.\n", (furthest_obstacle - curr_position).x, (furthest_obstacle - curr_position).y);
  DEBUG_PRINT("angle_correction %f.\n", angle_correction);
  DEBUG_PRINT("target_direction %f, target_distance %f.\n", target_direction_angle, target_distance);
  DEBUG_PRINT("evader_direction %f, %f.\n", evader_direction.x, evader_direction.y);
  DEBUG_PRINT("w %f.\n", w);
  DEBUG_PRINT("current_destination_angle %f.\n", current_destination_angle);
  return ret;
};

