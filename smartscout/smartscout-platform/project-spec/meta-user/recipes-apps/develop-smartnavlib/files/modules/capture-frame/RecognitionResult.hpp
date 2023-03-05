#ifndef __RECOGNITIONRESULT_H__
#define __RECOGNITIONRESULT_H__

#include <cstdint>

#include <nlohmann/json.hpp>

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
	/**
	 * @brief RecognitionResult to nlohmann json
	 * 
	 * @return nlohmann::json 
	 */
	nlohmann::json toJson() const {
		nlohmann::json json {
			{"label", label}, 
			{"score", score},
			{"ymin", ymin},
			{"xmin", xmin},
			{"ymax", ymax},
			{"xmax", xmax}
		};
		return json;
	};
	
};

#endif // __RECOGNITIONRESULT_H__