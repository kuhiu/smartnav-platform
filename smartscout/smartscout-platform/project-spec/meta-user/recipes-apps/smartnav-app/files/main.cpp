#include <signal.h>

#include <atomic>
#include <thread>

<<<<<<< HEAD:smartscout/smartscout-platform/project-spec/meta-user/recipes-apps/smartnav-app/files/main.cpp
#include <SmartNav.hpp>
#include <nlohmann/json.hpp>

//#define DEBUG_MAIN 1
#if defined(DEBUG_MAIN) 
 	#define DEBUG_PRINT(fmt, args...) printf( "DEBUG: %s:%d:%s(): " fmt, \
																						__FILE__, __LINE__, __func__, ##args)
#else
	#define DEBUG_PRINT(fmt, args...) /* Don't do anything in release builds */
=======
#include <smartnav.hpp>
#include <nlohmann/json.hpp>

//#define DEBUG_MAIN
#ifdef DEBUG_MAIN
#define DEBUG_PRINT(fmt, ...) fprintf(stderr, fmt, __VA_ARGS__)
#else
#define DEBUG_PRINT(fmt, ...) do {} while (0)
>>>>>>> master:smartscout/smartnav-platform/project-spec/meta-user/recipes-apps/smartnav-app/files/main.cpp
#endif

static std::atomic<bool> is_running{true};	

<<<<<<< HEAD:smartscout/smartscout-platform/project-spec/meta-user/recipes-apps/smartnav-app/files/main.cpp
=======
void frameCallback(std::shared_ptr<VirtualImage> img) {
	DEBUG_PRINT("Frame callback.\n");
  img->saveAsJpg("/tmp/test.jpg");
} 

>>>>>>> master:smartscout/smartnav-platform/project-spec/meta-user/recipes-apps/smartnav-app/files/main.cpp
void siginthandler(int param) {
  DEBUG_PRINT("User pressed Ctrl+C\n");
 	is_running = false;
}

int main(void) {
<<<<<<< HEAD:smartscout/smartscout-platform/project-spec/meta-user/recipes-apps/smartnav-app/files/main.cpp
	PositionEstimator::cartesianPosition where_we_go(100, 0);
	SmartNav smart_nav(where_we_go);

	signal(SIGINT, siginthandler);
=======
	smartnav smart_nav(frameCallback);
	
	signal(SIGINT, siginthandler);
	while (is_running.load()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	} 	
	DEBUG_PRINT("Main finished neatly.\n");
>>>>>>> master:smartscout/smartnav-platform/project-spec/meta-user/recipes-apps/smartnav-app/files/main.cpp
	return 0;
}
