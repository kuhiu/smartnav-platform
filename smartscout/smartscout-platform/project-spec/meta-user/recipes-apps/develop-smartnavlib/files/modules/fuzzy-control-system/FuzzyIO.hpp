#ifndef B9FCC8D6_8263_4C8E_B88D_F3485B9CC661
#define B9FCC8D6_8263_4C8E_B88D_F3485B9CC661

#include <memory>
#include <string>
#include <vector>

#include <FuzzyMembership.hpp>

class FuzzyIO {
public:
  /** FuzzyIO constructor */
  FuzzyIO(const std::string &name, std::vector<std::shared_ptr<FuzzyMembership>> memberships) : 
    __name(name), __memberships(memberships) {};
  /** FuzzyIO destructor */
  virtual ~FuzzyIO() = default;
  /**
   * @brief Get the memberships object
   * 
   * @return std::vector<std::shared_ptr<FuzzyMembership>> 
   */
  std::vector<std::shared_ptr<FuzzyMembership>> getMemberships() const { return __memberships; }; 
  /**
   * @brief Get the Name object
   * 
   * @return std::string 
   */
  std::string getName() const { return __name; };
  /**
   * @brief Reset all membership functions
   * 
   */
  void resetMembershipFuntions() {
    for (auto &mb : __memberships)
      mb->resetValue();
  };

protected:
	/** Input/Output name */
	std::string __name;
	/** Memberships function */
	std::vector<std::shared_ptr<FuzzyMembership>> __memberships;

};



#endif /* B9FCC8D6_8263_4C8E_B88D_F3485B9CC661 */
