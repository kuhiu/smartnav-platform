APP = frame-processor
SRC_FILES = main.cpp \
						modules/capture-frame/VirtualImage.cpp \
						modules/capture-frame/CaptureFrame.cpp \
						modules/Logger/Logger.cpp \
						modules/Logger/LogStream.cpp \
						Detector.cpp FrameProcessor.cpp

CFLAGS += -I$(INCLUDE) -I$(INCLUDE)/modules/Logger -I$(INCLUDE)/modules/capure-frame
LDLIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -ltensorflow-lite -ldl -lpthread

all: build

build: $(APP)

$(APP):
	$(CXX) -std=c++17 -o $@ $(SRC_FILES) $(LDFLAGS) $(LDLIBS) 
 
install: $(APP)
	cp $(APP) $(DESTDIR)/usr/bin
 
clean:
	rm -f $(APP) *.o

