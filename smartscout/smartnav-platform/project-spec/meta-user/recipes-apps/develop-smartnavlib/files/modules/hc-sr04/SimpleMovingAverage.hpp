#ifndef D3D8CA76_8456_4D4B_810F_1DD65A64F65E
#define D3D8CA76_8456_4D4B_810F_1DD65A64F65E

#include <queue>

class SimpleMovingAverage {
public:
  /** SimpleMovingAverage constructor */
  SimpleMovingAverage(int queue_len) : __queue_len(queue_len) {};
  /** SimpleMovingAverage destructor */
  ~SimpleMovingAverage() = default;
  /**
   * @brief Add data to the queue
   * 
   * @param data 
   */
  void addData(float data) {
    __sum += data;
    __queue.push(data);
    if (__queue.size() > __queue_len) {
      __sum -= __queue.front();
      __queue.pop();
    }
  };
  /**
   * @brief Get the Mean of the queue
   * 
   * @return float 
   */
  float getMean() { return __sum / __queue_len; };

private:
  /** Queue to store list */
  std::queue<float> __queue;
  /** Queue lenght */
  const int __queue_len;
  /** Queue summation */
  float __sum;

};

#endif /* D3D8CA76_8456_4D4B_810F_1DD65A64F65E */
