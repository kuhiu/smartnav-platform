#include <atomic>
#include <thread>

#include "modules/capture-frame/VirtualImage.hpp"
#include "modules/capture-frame/CaptureFrame.hpp"
#include "modules/hc-sr04/DistanceSensors.hpp"
#include "modules/logger/Logger.hpp"

void frameCallback(void* data, unsigned int size) {
  VirtualImage rgb_image(640, 480, 3, ColorSpaces::RGB, data);
  rgb_image.resize(320, 320);
  rgb_image.flip(false);
  rgb_image.colorBalancing(1.0);
  //rgb_image.saveAsJpg("testrgb.jpg");
}

int main(void) {
	std::atomic<bool> is_running;

	Logger::log() << "Im testing smartnavsys module";
	printf("Updated \n");
	DistanceSensors distance_sensor;
	//CaptureFrame capture_frame(frameCallback, 640, 480, CaptureFrame::pixelFormat::PIX_FMT_RGB24, 1);


	while (is_running.load()) {
		std::vector<int> distances = distance_sensor.getDistances();
		for (int i=0; i < distances.size(); i++)
			printf("Distance sensor %d: %d.\n", i, distances[i]);
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	return 0;
}
