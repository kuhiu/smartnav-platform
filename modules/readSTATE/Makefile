TARGET = readSTATE
GCC = arm-linux-gnueabihf-gcc
SRC_DIR 	:= ./src
OBJ_DIR 	:= ./obj
INC_DIR 	:= ./inc
OUTPUT_DIR	:= ../../gen/readSTATE
SRC_FILES 	:= $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES 	:= $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))
LDFLAGS 	:= 
CPPFLAGS 	:= 
CXXFLAGS 	:= -Wall 
LIBS		:= -lm

$(TARGET): $(OBJ_FILES)
	mkdir -p $(OUTPUT_DIR)
	$(GCC) $(LDFLAGS) -o $(OUTPUT_DIR)/$@ $^ $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(GCC) $(CXXFLAGS) -c -o $@ $< -I$(INC_DIR) $(LIBS)
