APP_NAME  = smartnav-app
SUBDIR = ./ 

OBJECTS_DIR = ./obj

HEADERS = $(wildcard *.hpp $(foreach fd, $(SUBDIR), $(fd)/*.hpp))
SOURCES = $(wildcard *.cpp $(foreach fd, $(SUBDIR), $(fd)/*.cpp))
OBJECTS = $(addprefix $(OBJECTS_DIR)/, $(SOURCES:cpp=o))
INCLUDE_DIRS = $(addprefix -I, $(SUBDIR))

all: $(APP_NAME)

$(LIB_NAME): $(OBJECTS)
	@echo Compiling $(APP_NAME)
	$(CXX) $(OBJECTS) -o $(APP_NAME) -lsmartnavsys

$(OBJECTS_DIR)/%.o: %.cpp $(HEADERS)
	mkdir -p $(@D)
	@echo Compiling $@
	$(CXX) $(CXXFLAGS) -o $@ $< $(INCLUDE_DIRS) -lsmartnavsys

install: $(APP_NAME)
	cp $(APP_NAME) $(DESTDIR)/usr/bin

clean:
	rm -rf $(OUTPUT_DIR)/* $(OBJECTS_DIR)/*