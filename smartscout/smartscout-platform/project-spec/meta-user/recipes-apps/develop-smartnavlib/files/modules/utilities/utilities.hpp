#ifndef CA3B3897_B288_488A_A614_DDBFCDA9CF19
#define CA3B3897_B288_488A_A614_DDBFCDA9CF19

class utilities {
public:
  /** Utilities constructor */
  utilities();
  /** Utilities destructor */
  ~utilities();

  
private:

};
    // Start measuring time
    auto begin = std::chrono::system_clock::now();

		auto end = std::chrono::system_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
		printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
#endif /* CA3B3897_B288_488A_A614_DDBFCDA9CF19 */
