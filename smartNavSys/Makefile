TARGET = smartNavSys
CXX = arm-linux-gnueabihf-g++
SRC_DIR 	:= .
OBJ_DIR 	:= ./obj
INC_DIR 	:= -I. -I./fuzzyControl -I./fuzzyControl/fuzzyRule
OUTPUT_DIR	:= ./gen/$(TARGET)
SRC_FILES 	:= $(wildcard $(SRC_DIR)/*.cpp $(SRC_DIR)/fuzzyControl/*.cpp $(SRC_DIR)/fuzzyControl/fuzzyRule/*.cpp)
OBJ_FILES 	:= $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
LDFLAGS 	:= -Wall -std=c++11
CPPFLAGS 	:= 
CXXFLAGS 	:= -Wall -std=c++11
LIBS		:= -lm

$(TARGET): $(OBJ_FILES)
	mkdir -p $(OUTPUT_DIR)
	$(CXX) -o $(OUTPUT_DIR)/$@ $^ $(LIBS) $(LDFLAGS)
	cp $(SRC_DIR)/state.txt $(OUTPUT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR) $(OBJ_DIR)/fuzzyControl $(OBJ_DIR)/fuzzyControl/fuzzyRule 
	$(CXX) -c -o $@ $< $(INC_DIR) $(LIBS) $(CXXFLAGS)

clean: 
	rm -r $(OUTPUT_DIR) $(OBJ_DIR)
