
#ifndef _V_CSC_CONFIG_H_
#define _V_CSC_CONFIG_H_

#define SAMPLES_PER_CLOCK       1
#define MAX_COLS                1080
#define MAX_ROWS                720
#define MAX_DATA_WIDTH          8

#define NUM_VIDEO_COMPONENTS    3
#define BITS_PER_SAMPLE         (3*MAX_DATA_WIDTH)
#define BITS_PER_CLOCK          (BITS_PER_SAMPLE*SAMPLES_PER_CLOCK)

#define ENABLE_422              1
#define ENABLE_420              1
#define ENABLE_WINDOW           0

#define USE_URAM                0

#endif
