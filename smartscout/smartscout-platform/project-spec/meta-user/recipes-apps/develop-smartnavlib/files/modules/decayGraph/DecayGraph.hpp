#ifndef D286E000_3ADD_4016_8918_CE27DC6B14E4
#define D286E000_3ADD_4016_8918_CE27DC6B14E4

class DecayGraph {
public:
  /** DecayGraph constructor */
  DecayGraph() = default;
  /** DecayGraph destructor */
  ~DecayGraph() = default;
  /**
   * @brief Compute the decay graph 
   * 
   * @param value 
   * @return float 
   */
  float compute() { 
    float func = (-__MAX_VALUE/__TIME_MSEG) * __value + __MAX_VALUE;
    if (func < 0)
      func = 0;
    else if (func > 0)
      func = __MAX_VALUE;
    return func; 
  };
  /**
   * @brief Reset the value of the graph value 
   * 
   */
  void reset() { __value = 0; }
  /**
   * @brief Load time to the decay graph
   * 
   * @param value 
   */
  void loadTime(float value) { __value = __value + value; }

private:
  /** Max time of the decay graph */
  const float __TIME_MSEG = 2000;
  /** Max value of the decay graph */
  const float __MAX_VALUE = 100;
  /** Current value */
  float __value = 0;

};

#endif /* D286E000_3ADD_4016_8918_CE27DC6B14E4 */
