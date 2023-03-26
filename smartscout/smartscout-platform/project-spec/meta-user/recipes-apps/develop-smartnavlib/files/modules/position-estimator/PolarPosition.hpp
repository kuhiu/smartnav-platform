#ifndef A9C4C27B_8C18_4EB5_93F5_A264FC6445A6
#define A9C4C27B_8C18_4EB5_93F5_A264FC6445A6

/** polarPosition struct */
struct PolarPosition {
  /** angle estimation [degree] */
  float angle;
  /** distance estimation [cm] */
  float distance;
  /** polarPosition constructor */
  PolarPosition() = default;
  /** polarPosition constructor */
  PolarPosition(float angle, float distance) : angle(angle), distance(distance) {};

};

#endif /* A9C4C27B_8C18_4EB5_93F5_A264FC6445A6 */
