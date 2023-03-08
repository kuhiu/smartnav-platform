#include <signal.h>

#include <atomic>
#include <thread>

#include <SmartNav.hpp>
#include <nlohmann/json.hpp>

//#define DEBUG_MAIN 1
#if defined(DEBUG_MAIN) 
 	#define DEBUG_PRINT(fmt, args...) printf( "DEBUG: %s:%d:%s(): " fmt, \
																						__FILE__, __LINE__, __func__, ##args)
#else
	#define DEBUG_PRINT(fmt, args...) /* Don't do anything in release builds */
#endif

static std::atomic<bool> is_running{true};	

void siginthandler(int param) {
  DEBUG_PRINT("User pressed Ctrl+C\n");
 	is_running = false;
}

int main(void) {
	/** Sigint setup */
	signal(SIGINT, siginthandler);
	
	CartesianPosition where_we_go(100, 0);
	SmartNav smart_nav(where_we_go);

	while (is_running && smart_nav.isRunning())
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	
	return 0;
}
