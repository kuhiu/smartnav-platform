APP = smartnavsys
SRC_FILES = main.cpp \
						modules/capture-frame/VirtualImage.cpp \
						modules/capture-frame/CaptureFrame.cpp \
						modules/frame-processor/Detector.cpp \
						modules/frame-processor/FrameProcessor.cpp \
						modules/hc-sr04/DistanceSensors.cpp \
						modules/logger/Logger.cpp \
						modules/logger/LogStream.cpp 

CFLAGS += -I$(INCLUDE) \
					-I$(INCLUDE)/modules/logger \
					-I$(INCLUDE)/modules/capure-frame \
					-I$(INCLUDE)/modules/hc-sr04 \
					-I$(INCLUDE)/modules/frame-processor
					
LDLIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -ltensorflow-lite -ldl -lpthread

all: build

build: $(APP)

$(APP):
	$(CXX) -std=c++17 -o $@ $(SRC_FILES) $(LDFLAGS) $(LDLIBS) 
 
install: $(APP)
	cp $(APP) $(DESTDIR)/usr/bin
 
clean:
	rm -f $(APP) *.o

