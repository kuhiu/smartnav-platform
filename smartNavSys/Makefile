TARGET = main
CXX = arm-linux-gnueabihf-g++
OPENCV_DIR	:= ./OpenCV/
SRC_DIR 	:= .
OBJ_DIR 	:= ./obj
INC_DIR 	:= -I. -I./fuzzyControl -I./fuzzyControl/fuzzyRule -I./OpenCV/include
OUTPUT_DIR	:= ./gen/$(TARGET)
SRC_FILES 	:= $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/fuzzyControl/*.cpp $(SRC_DIR)/fuzzyControl/fuzzyRule/*.cpp)
OBJ_FILES 	:= $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
LDFLAGS 	:= -Wall -std=c++11
CPPFLAGS 	:= 
CXXFLAGS 	:= -Wall -std=c++11
LIBS		:= 	-lm \
				-L$(OPENCV_DIR)/lib \
				-lopencv_core -lopencv_imgproc -lopencv_imgcodecs \
				-lopencv_highgui -lopencv_calib3d -lopencv_features2d \
				-lopencv_flann -lopencv_ml -lopencv_objdetect -lopencv_photo \
				-lopencv_superres -lopencv_video -lopencv_videostab -lopencv_videoio -pthread 

$(TARGET): $(OBJ_FILES)
	mkdir -p $(OUTPUT_DIR)
	$(CXX) -o $(OUTPUT_DIR)/$@ $^ $(LIBS) $(LDFLAGS)
	cp $(SRC_DIR)/state.txt $(OUTPUT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR) $(OBJ_DIR)/fuzzyControl $(OBJ_DIR)/fuzzyControl/fuzzyRule 
	$(CXX) -c -o $@ $< $(INC_DIR) $(LIBS) $(CXXFLAGS)

clean: 
	rm -r $(OUTPUT_DIR) $(OBJ_DIR)
