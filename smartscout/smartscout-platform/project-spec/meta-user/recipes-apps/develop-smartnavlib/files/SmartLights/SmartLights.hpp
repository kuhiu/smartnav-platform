#ifndef CE941919_8490_46C7_989E_F57DFFA2733A
#define CE941919_8490_46C7_989E_F57DFFA2733A

#include <fstream>
#include <memory>

#include <FuzzyControlSystem.hpp>

#include <nlohmann/json.hpp>

class SmartLights {
public:
  /** SmartLights constructor */
  SmartLights() {
    // Parse fuzzy system file 
    std::ifstream fuzzy_system_s1_file(__FUZZY_S1_JSON);
    const nlohmann::json fuzzy_system_s1_json = nlohmann::json::parse(fuzzy_system_s1_file);
    // Create fuzzy control system object
    __fuzzy_system_stage_1 = std::make_shared<FuzzyControlSystem>(FuzzyControlSystem::parse(fuzzy_system_s1_json));
  };
  /** SmartLights destructor */
  ~SmartLights() = default;
  /**
   * @brief Evaluate the input with the fuzzy control system
   * 
   * @return float 
   */
  float evaluate(float brightness) {
    float ret = -1;
    std::vector<std::pair<std::string, float>> inputs;
    std::vector<FuzzyOutput> outputs;
    
    // Fuzzy control system: Stage 1 
    inputs = { {"lighting", brightness} };
    // Evaluate fuzzy system
    outputs = __fuzzy_system_stage_1->evaluate(inputs);
    // Read outputs 
    for (FuzzyOutput &output : outputs) {
      if (output.getName() == "car_headlights") 
        ret = output.defuzzification();
    }  
    return ret;
  }

private:
  /** JSON file which describes the fuzzy system */
  static constexpr auto __FUZZY_S1_JSON{"/usr/bin/SmartLights-stage-1.json"};
  /** Fuzzy control system object: STAGE 1 */
  std::shared_ptr<FuzzyControlSystem> __fuzzy_system_stage_1;

};



#endif /* CE941919_8490_46C7_989E_F57DFFA2733A */
