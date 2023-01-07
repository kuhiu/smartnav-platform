LIB_NAME  = smartnavsys
SUBDIR = modules/capture-frame modules/frame-processor modules/hc-sr04 modules/fuzzy-control-system

OBJECTS_DIR = ./obj

HEADERS = $(wildcard *.hpp $(foreach fd, $(SUBDIR), $(fd)/*.hpp))
SOURCES = $(wildcard *.cpp $(foreach fd, $(SUBDIR), $(fd)/*.cpp))
OBJECTS = $(addprefix $(OBJECTS_DIR)/, $(SOURCES:cpp=o))
INCLUDE_DIRS = $(addprefix -I, $(SUBDIR))

CFLAGS_LIB = -std=c++17 -c -fPIC 
LDFLAGS_LIB = -shared -Wl,-soname,lib$(LIB_NAME).so.0
LDLIBS_LIB = -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -ltensorflow-lite -ldl -lpthread

all: lib$(LIB_NAME).so

lib$(LIB_NAME).so: $(OBJECTS)
	@echo Compiling lib$(LIB_NAME).so
	$(CXX) $(OBJECTS) -o lib$(LIB_NAME).so.0.0.23 $(LIBS) $(LDFLAGS) $(LDFLAGS_LIB) $(LDLIBS_LIB)

$(OBJECTS_DIR)/%.o: %.cpp $(HEADERS)
	mkdir -p $(@D)
	@echo Compiling $@
	$(CXX) -o $@ -c $< $(CFLAGS) $(CFLAGS_LIB) $(INCLUDE_DIRS)

install: lib$(LIB_NAME).so
	cp lib$(LIB_NAME).so $(DESTDIR)/usr/lib

clean:
	rm -rf $(OUTPUT_DIR)/* $(OBJECTS_DIR)/*