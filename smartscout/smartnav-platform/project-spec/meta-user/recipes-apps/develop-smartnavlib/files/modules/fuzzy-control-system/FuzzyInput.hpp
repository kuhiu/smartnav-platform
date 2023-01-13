#ifndef A1CF177A_D590_4AAB_8FFF_1D4A89E5B341
#define A1CF177A_D590_4AAB_8FFF_1D4A89E5B341

#include <memory>
#include <string>
#include <vector>

#include <FuzzyIO.hpp>
#include <FuzzyMembershipTrapezoidal.hpp>

#include <nlohmann/json.hpp>

using namespace nlohmann;

class FuzzyInput : public FuzzyIO {
public:
  /** FuzzyInput constructor */
  FuzzyInput(const std::string &name, std::vector<std::shared_ptr<FuzzyMembership>> memberships) : 
    FuzzyIO(name, memberships) {};
  /** FuzzyInput destructor */
  virtual ~FuzzyInput() = default;
  /**
   * @brief Input fuzzification
   * 
   */
	void fuzzyfication(float input_value);
  /**
   * @brief Try to parse input
   * 
   * @param io input to parse
   * @return FuzzyInput 
   */
  static FuzzyInput parse(const nlohmann::json& input_json);

private:
  /** Membership function key */
  static constexpr auto __MEMBERSHIPS_FUNCTIONS_KEY{"membership_functions"};
  /** Name key */
  static constexpr auto __NAME_KEY{"name"};
  
};



#endif /* A1CF177A_D590_4AAB_8FFF_1D4A89E5B341 */
