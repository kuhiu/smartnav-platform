#include <signal.h>

#include <atomic>
#include <thread>

#include <SmartNav.hpp>
#include <nlohmann/json.hpp>

//#define DEBUG_MAIN
#ifdef DEBUG_MAIN
#define DEBUG_PRINT(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...) do {} while (0)
#endif

static std::atomic<bool> is_running{true};	

void siginthandler(int param) {
  DEBUG_PRINT("User pressed Ctrl+C\n");
 	is_running = false;
}

int main(void) {
	SmartNav smart_nav();
	
	signal(SIGINT, siginthandler);
	while (is_running.load()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	} 	
	DEBUG_PRINT("Main finished neatly.\n");
	return 0;
}
