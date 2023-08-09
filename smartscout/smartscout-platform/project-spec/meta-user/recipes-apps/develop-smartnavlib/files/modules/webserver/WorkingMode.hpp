#ifndef C3281D92_DB4C_4779_9384_E7207A93123E
#define C3281D92_DB4C_4779_9384_E7207A93123E

/**
 * @brief Working modes
 * 
 */
enum WorkingMode {
  /**
   * @brief DEFAULT, The user can control the rc 
   * car by the android app. This mode is always 
   * working.
   * 
   */
  DEFAULT = 0,
  /**
   * @brief AUTOMATIC_EVASION, During the DEFAULT operating mode 
   * the user can ask for an automatic evasion.  
   * 
   */
  AUTOMATIC_EVASION,
  /**
   * @brief SET_TARGET, The user can select where to go sending
   * a Cartesian Position relative to the actual position. 
   * 
   */
  SET_TARGET,

};

#endif /* C3281D92_DB4C_4779_9384_E7207A93123E */
