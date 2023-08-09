SUBDIR = modules/pixel-magic modules/camera-sender modules/buttons modules/reporter modules/tracker modules/frame-processor modules/obstacle modules/capture-frame modules/distance-sensors modules/fuzzy-control-system modules/driver modules/headlights modules/compass modules/mailbox modules/position-estimator modules/decayGraph modules/webserver SmartEvasion SmartLights 

OBJECTS_DIR = ./obj

HEADERS = $(wildcard *.hpp $(foreach fd, $(SUBDIR), $(fd)/*.hpp))
SOURCES = $(wildcard *.cpp $(foreach fd, $(SUBDIR), $(fd)/*.cpp))
OBJECTS = $(addprefix $(OBJECTS_DIR)/, $(SOURCES:cpp=o))
INCLUDE_DIRS = $(addprefix -I, $(SUBDIR))

CFLAGS_LIB = -std=c++17 -c -fPIC -O3
LDFLAGS_LIB = -shared -Wl,-soname,$(LIB_NAME).so.0
LDLIBS_LIB = -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_videoio -lopencv_imgcodecs -ltensorflow-lite -lopencv_xphoto -ldl -lpthread -li2c

all: $(LIB_NAME).so

$(LIB_NAME).so: $(OBJECTS)
	@echo Compiling $(LIB_NAME).so
	$(CXX) $(OBJECTS) -o $(LIB_NAME).so.$(LIB_VERSION) $(LIBS) $(LDFLAGS) $(LDFLAGS_LIB) $(LDLIBS_LIB)

$(OBJECTS_DIR)/%.o: %.cpp $(HEADERS)
	mkdir -p $(@D)
	@echo Compiling $@
	$(CXX) -o $@ -c $< $(CFLAGS) $(CFLAGS_LIB) $(INCLUDE_DIRS)

install: $(LIB_NAME).so
	cp $(LIB_NAME).so $(DESTDIR)/usr/lib

clean:
	rm -rf *.so *.so.* $(OBJECTS_DIR)/*