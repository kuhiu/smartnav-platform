#include <chrono>
#include <iostream>
#include <stdio.h>

#define FRAMEBUFFER_READ_OFFSET 0x01000000  // phy image offset

#include "Detector.hpp"
#include "PhyImage.hpp"

#include <sys/types.h> // Borrar
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <opencv2/opencv.hpp>

int main() {
  /** Image width */
  const int width = 320;
  /** Image height */
  const int height = 320;
  /** Image channel */
  const int channels = 1;
  /** Main status */
  bool isRunning = true;
  /** PersonDetector */
  printf("Create detector\n");
  Detector detector;
  /** PhyImage */
  printf("Create phy image\n");
  PhyImage physical_image(320, 240, 4, (off_t)FRAMEBUFFER_READ_OFFSET);

  int fd;
  printf("Open vdma driver\n");
  if ( (fd = open("/dev/vdma_control_chardev", O_RDWR)) == -1){
      printf("Error abriendo vdma_control_chardev! %s\n", strerror(errno));
      return -1;
  }

  while (isRunning) {
    /** Create a virtual image */
    printf("Create virtual image\n");
    VirtualImage virtual_image(physical_image.getWidth(), physical_image.getHeigth(), 
        physical_image.getChannels(), colorSpace(RGBA), physical_image.getData());

    printf("Save RGBA into a file\n");
    virtual_image.saveAsJpg("./rgba.jpg");

    virtual_image.rgbaToRgb();

    printf("Save RGB into a file\n");
    virtual_image.saveAsJpg("./rgb.jpg");

    printf("virtual_image resize\n");
    virtual_image.resize(width, height);

    printf("Save resize into a file\n");
    virtual_image.saveAsJpg("./resize.jpg");

    // Start measuring time
    auto begin = std::chrono::high_resolution_clock::now();

    /** Run Person detector */
    printf("detect\n");
    std::vector<RecognitionResult> recognitions_result = detector.detect(virtual_image);

    // Stop measuring time and calculate the elapsed time
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    /** Print results */
    std::cout << "Number of object recognized = " << recognitions_result.size() << std::endl;

    std::cout << "Time recognition" << (elapsed.count() * 1e-9) << "seconds" << std::endl;
  }

  close(fd);
  return 0;
}