TARGET 		= smartNavSys
CC 			= arm-linux-gnueabihf-gcc
CXX 		= arm-linux-gnueabihf-g++
SRC_DIR 	:= ./src
OBJ_DIR 	:= ./obj
INC_DIR 	:= ./inc
OUTPUT_DIR	:= ../../gen/$(TARGET)
SRC_FILES 	:= $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES 	:= $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
LDFLAGS 	:= -Wall -std=c++11 -lstdc++fs
CPPFLAGS 	:= 
CXXFLAGS 	:= -Wall -std=c++11 -lstdc++fs
LIBS		:= -lm

$(TARGET): $(OBJ_FILES)
	mkdir -p $(OUTPUT_DIR)
	$(CXX) -o $(OUTPUT_DIR)/$@ $^ $(LIBS) $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) -c -o $@ $< -I$(INC_DIR) $(LIBS) $(CXXFLAGS)
