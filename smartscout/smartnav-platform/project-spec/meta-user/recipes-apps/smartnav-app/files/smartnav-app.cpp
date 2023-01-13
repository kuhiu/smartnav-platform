#include <signal.h>

#include <atomic>
#include <thread>

#include "VirtualImage.hpp"
#include "CaptureFrame.hpp"
#include "DistanceSensors.hpp"
#include "FuzzyControlSystem.hpp"

#include <nlohmann/json.hpp>

static std::atomic<bool> is_running{true};		// main state

void frameCallback(void* data, unsigned int size) {
	printf("Frame callback.\n");
  VirtualImage rgb_image(640, 480, 3, ColorSpaces::RGB, data);
  rgb_image.resize(320, 320);
  rgb_image.flip(false);
  rgb_image.colorBalancing(1.0);
  rgb_image.saveAsJpg("testrgb.jpg");
} 

void siginthandler(int param) {
  printf("User pressed Ctrl+C\n");
 	is_running = false;
}

int main(void) {
	/** Charge sigint interrupt */
	signal(SIGINT, siginthandler);
	/** Create a Distance sensor object */
	DistanceSensors distance_sensor;
	/** Parse fuzzy system file */
	std::ifstream fuzzy_system_file("./fuzzy_system_v0.json");
	const json fuzzy_system_json = json::parse(fuzzy_system_file);
	/** Create fuzzy control system object  */
	printf("Fuzzy control system parse. %s\n", fuzzy_system_json.dump().c_str());
	FuzzyControlSystem fuzzy_system = FuzzyControlSystem::parse(fuzzy_system_json);
	/** Create Capture frame object */
	CaptureFrame capture_frame(frameCallback, 640, 480, CaptureFrame::pixelFormat::PIX_FMT_RGB24, 1);
	
	/** Infinite loop */
	while (is_running.load()) {
		std::vector<std::pair<std::string, float>> inputs;
		std::vector<int> distances = distance_sensor.getDistances();

		if (distances.size() != 3)
		 throw std::runtime_error("Not three sensor outputs.");

		for (int i=0; i < distances.size(); i++)
			printf("Distance sensor %d: %d.\n", i, distances[i]);
		
		inputs = {  {"left_distance_sensor", (float)distances[0]},
		 						{"center_distance_sensor", (float)distances[1]}, 
								{"right_distance_sensor", (float)distances[2]} };

		auto outputs = fuzzy_system.evaluate(inputs);

		printf("outputs size: %d.\n", outputs.size());

		for (FuzzyOutput &out : outputs) 
			printf("Output: %s, value: %f.\n", out.getName().c_str(), out.defuzzification() );
		

		std::this_thread::sleep_for(std::chrono::seconds(1));
	} 

	printf("Main finished neatly.\n");
	return 0;
}
