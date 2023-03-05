#ifndef FEF550E2_5D36_4158_9C26_037747CBD30B
#define FEF550E2_5D36_4158_9C26_037747CBD30B

#include <math.h>

#include <string>

#include <nlohmann/json.hpp>

#include <FuzzyMembership.hpp>

using namespace nlohmann;

class FuzzyMembershipTrapezoidal : public FuzzyMembership {
public:
	/*	
	TrapezoidalPoints
							-------------				
		slope1  /								\  slope2
					 -------------------
				 x1							     x2
	*/
	struct TrapezoidalPoints {
		/** Smallest x point */
		float x1;
		/** Higher x point */
		float x2;             
		/** Right slope */
		float right_slope;             
		/** Left slope */
		float left_slope; 
	};
	/** FuzzyMembershipTrapezoidal constructor */
	FuzzyMembershipTrapezoidal(const std::string &name, TrapezoidalPoints trapezoidal_points) 
		: __trapezoidal_points(trapezoidal_points), FuzzyMembership(name) {};
	/** FuzzyMembershipTrapezoidal destructor */
	virtual ~FuzzyMembershipTrapezoidal() = default;
	/**
	 * @brief Compute area of the trapezoid
	 * 
	 * @param value 
	 * @return float 
	 */
	virtual float compute_area_of_membership();
	/**
	 * @brief Compute centroid of membership
	 * 
	 * @return float 
	 */
	virtual float compute_centroid_of_membership();
	/**
	 * @brief Evaluate membership function (membership degree)
	 * 
	 * @param value 
	 */
	virtual void compute_degree_of_membership(float input_value) override;
	/**
	 * @brief Try to parse membership function
	 * 
	 * @param input_json 
	 * @return FuzzyMembershipTrapezoidal 
	 */
	static FuzzyMembershipPtr parse(const nlohmann::json& memb_function_json);

  /** Trapezoidal memebership function key */
  static constexpr auto __MB_TRAPEZOIDAL_KEY{"trapezoidal"};
	
private:
  /** Name key */
  static constexpr auto __NAME_KEY{"name"};
  /** Trapezoidal Points keys */
  static constexpr auto __MB_X1_KEY{"x1"};
	static constexpr auto __MB_X2_KEY{"x2"};
	static constexpr auto __MB_RIGHT_SLOPE_KEY{"right_slope"};
	static constexpr auto __MB_LEFT_SLOPE_KEY{"left_slope"};
	/** Trapezoidal membership function */
	TrapezoidalPoints __trapezoidal_points;

};



#endif /* FEF550E2_5D36_4158_9C26_037747CBD30B */
