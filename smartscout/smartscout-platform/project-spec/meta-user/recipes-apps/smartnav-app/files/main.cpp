#include <signal.h>

#include <atomic>
#include <thread>
#include <chrono>

#include <SmartNav.hpp>
#include <nlohmann/json.hpp>

#define DEBUG_MAIN 1
#if defined(DEBUG_MAIN) 
 	#define DEBUG_PRINT(fmt, args...) printf( "DEBUG: %s:%d:%s(): " fmt, \
																						__FILE__, __LINE__, __func__, ##args)
#else
	#define DEBUG_PRINT(fmt, args...) /* Don't do anything in release builds */
#endif

static std::atomic<bool> is_running{true};	

void siginthandler(int param) { is_running = false; }

int main(int argc, char* argv[]) {
	/** Sigint setup */
	signal(SIGINT, siginthandler);

	if (argc < 3) {
		std::cout << "Usage: ./program_name img_width img_height framerate" << std::endl;
		return 1;
	}
	int img_width = std::stoi(argv[1]);
	int img_height = std::stoi(argv[2]);
	int img_framerate = std::stoi(argv[3]);
	SmartNav smart_nav(img_width, img_height, img_framerate);
	while (is_running) {
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}	
	
	return 0;
}