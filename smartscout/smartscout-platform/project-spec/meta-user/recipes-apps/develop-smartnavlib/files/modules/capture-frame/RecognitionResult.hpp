#ifndef __RECOGNITIONRESULT_H__
#define __RECOGNITIONRESULT_H__

#include <cstdint>

struct RecognitionResult {
	/** Class label */
	int label;
	/** Class score */
	float score;
	/** Y-axis minimum value */
	float ymin;
	/** X-axis minimum value */
	float xmin;
	/** Y-axis maximum value */
	float ymax;
	/** X-axis maximum value*/
	float xmax;

};

#endif // __RECOGNITIONRESULT_H__