#include <signal.h>

#include <atomic>
#include <thread>

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

int main(void) {
	/** Sigint setup */
	signal(SIGINT, siginthandler);
	Buttons buttons;
	SmartNav smart_nav;

	while (is_running) {
		DEBUG_PRINT("Reading buttons!!...\n");
		// Read buttons of zybo board (blocking) 
		ButtonNum ret = buttons.read();
		DEBUG_PRINT("Button: %d.\n", ret);
		switch (ret) {
		case ButtonNum::BUTTON_0:
		{
			CartesianPosition target(100, 0);
			smart_nav.newTarget(target);
		}
			break;
		case ButtonNum::BUTTON_1:
		{
			CartesianPosition target(100, 100);
			smart_nav.newTarget(target);
		}
			break;
		case ButtonNum::BUTTON_2:
		{
			CartesianPosition target(100, -100);
			smart_nav.newTarget(target);
		}
			break;
		case ButtonNum::BUTTON_3:
		{
			CartesianPosition target(-100, 0);
			smart_nav.newTarget(target);
		}
			break;
		default:
			break;
		}
	}	
	return 0;
}
