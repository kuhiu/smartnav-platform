#ifndef E2FEBB06_2742_47AF_A486_87D711A3E209
#define E2FEBB06_2742_47AF_A486_87D711A3E209

#include <string>

class FuzzyMembership {
public:
  /** FuzzyMembership smart pointer */
  using FuzzyMembershipPtr = std::shared_ptr<FuzzyMembership>;
	/** FuzzyMembership constructor */
	FuzzyMembership(const std::string &name) : __name(name) {};
	/** FuzzyMembership destructor */
	virtual ~FuzzyMembership() = default;
	/**
	 * @brief Compute degree of membership
	 * 
	 * @param value 
	 */
	virtual void compute_degree_of_membership(float input_value) = 0;
	/**
	 * @brief Compute area of membership
	 * 
	 * @return float 
	 */
	virtual float compute_area_of_membership() = 0;
	/**
	 * @brief Compute centroid of membership
	 * 
	 * @return float 
	 */
	virtual float compute_centroid_of_membership() = 0;
	/**
	 * @brief Get the Name object
	 * 
	 * @return std::string 
	 */
	std::string getName() const { return __name; };
	/**
	 * @brief Get the Value object
	 * 
	 * @return float 
	 */
	float getValue() const { return __fuzzy_value; };
	/**
	 * @brief Set the Value object
	 * 
	 * @param value 
	 */
	void setValue(float value) { __fuzzy_value = value; }
	/**
	 * @brief Reset fuzzy value 
	 * 
	 */
	void resetValue() { __fuzzy_value = 0; };

protected:
  /** Name key */
  static constexpr auto __NAME_KEY{"name"};
  /** Max membership value */
  const float __UPPER_LIMIT = 1.0;
	/** Fuzzy value */
	float __fuzzy_value = 0.0;                 
	/** FuzzyMembership name */
  const std::string __name;   
	
};



#endif /* E2FEBB06_2742_47AF_A486_87D711A3E209 */
