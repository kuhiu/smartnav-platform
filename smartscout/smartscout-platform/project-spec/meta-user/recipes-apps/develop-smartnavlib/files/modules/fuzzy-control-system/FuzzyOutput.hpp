#ifndef AC7E2957_4A9D_46EE_A10F_D46F2E695892
#define AC7E2957_4A9D_46EE_A10F_D46F2E695892

#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include <FuzzyMembership.hpp>
#include <FuzzyIO.hpp>

#include <nlohmann/json.hpp>

using namespace nlohmann;

class FuzzyOutput : public FuzzyIO {
public:
	/** FuzzyOutput constructor */
	FuzzyOutput(const std::string &name, std::vector<std::shared_ptr<FuzzyMembership>> memberships) : 
		FuzzyIO(name, memberships) {};
	/** FuzzyOutput destructor */
	virtual ~FuzzyOutput() = default;
	/**
	 * @brief Membership defuzzification
	 * 
	 * @return float 
	 */
	float defuzzification();
  /**
   * @brief Try to parse output
   * 
   * @param io input to parse
   * @return FuzzyInput 
   */
  static FuzzyOutput parse(const nlohmann::json& output_json);

private:
  /** Membership function key */
  static constexpr auto __MEMBERSHIPS_FUNCTIONS_KEY{"membership_functions"};
  /** Name key */
  static constexpr auto __NAME_KEY{"name"};

};

#endif /* AC7E2957_4A9D_46EE_A10F_D46F2E695892 */
