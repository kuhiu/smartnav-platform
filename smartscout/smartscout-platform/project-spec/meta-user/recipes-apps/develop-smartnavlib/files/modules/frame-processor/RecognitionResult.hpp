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
	/** RecognitionResult constructor */
	RecognitionResult() = default;
	/** RecognitionResult destructor */
	~RecognitionResult() = default;
	/**
	 * @brief Construct a new Recognition Result object
	 * 
	 * @param source 
	 */
	RecognitionResult(const RecognitionResult& source) : 
			label{source.label}, score{source.score}, ymin{source.ymin},
			xmin{source.xmin}, ymax{source.ymax}, xmax{source.xmax} {};
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