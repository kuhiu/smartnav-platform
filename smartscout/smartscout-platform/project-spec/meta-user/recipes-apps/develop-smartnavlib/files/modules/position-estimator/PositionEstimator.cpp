#include <PositionEstimator.hpp>

//#define DEBUG_POSESTIMATOR 1
#ifdef DEBUG_POSESTIMATOR
 	#define DEBUG_PRINT(fmt, args...) printf( "DEBUG: %s:%d:%s(): " fmt, \
																						__FILE__, __LINE__, __func__, ##args)
#else
	#define DEBUG_PRINT(fmt, args...) /* Don't do anything in release builds */
#endif

PositionEstimator::PositionEstimator() {
  // Turn on the led to indicate the microblaze is running
  __mailbox.sendBlocking(mailbox::command::LED_CTRL, 0x01);
  // Current position
  __curr_position.x = 0;
  __curr_position.y = 0;
  // Start thread
  __is_running = true;
  __encoders_thread = std::thread(&PositionEstimator::__readEncoders, this);
};

PositionEstimator::~PositionEstimator() {
  __is_running = false;
  __encoders_thread.join();
};

CartesianPosition PositionEstimator::getCurrentPosition () {
  CartesianPosition ret;

  { // thread safe
    std::lock_guard<std::mutex> lock(__m);
    ret = __curr_position;
  }
  return ret;
};

void PositionEstimator::__readEncoders() {
  PolarPosition polar;

  while (__is_running) {
    // Ask to microblaze the encoder count and save value
    __mailbox.sendBlocking(mailbox::command::ENCODER_1_COUNT, 0x00);
    encoder1_queue.push(__mailbox.receiveBlocking());
    if (encoder1_queue.size() > __QUEUE_LEN) 
      encoder1_queue.pop();
    // Ask to microblaze the encoder count and save value
    __mailbox.sendBlocking(mailbox::command::ENCODER_2_COUNT, 0x00);
    encoder2_queue.push(__mailbox.receiveBlocking());
    if (encoder2_queue.size() > __QUEUE_LEN) 
      encoder2_queue.pop();
    // Get current count 
    int encoder1_curr = encoder1_queue.back() - encoder1_queue.front();
    int encoder2_curr = encoder2_queue.back() - encoder2_queue.front();
    // The movement of the robot is composed of a translation and a rotation. 
    // I assume that the robot moves towards a direction when both motors move 
    // at the same speed, because when one works faster the robot will start to 
    // rotate towards that direction.
    if (encoder2_curr > encoder1_curr)
      polar.distance = __countToDistance(encoder1_curr);
    else 
      polar.distance = __countToDistance(encoder2_curr);
    polar.angle = __compass.getValue();
    DEBUG_PRINT("polar.angle %f, polar.distance %f.\n", polar.angle, polar.distance);
    auto cart = polarToCartesian(polar);
    { // thread safe
      std::lock_guard<std::mutex> lock(__m);
      __curr_position.x += cart.x;
      __curr_position.y += cart.y;
    }
  }
};