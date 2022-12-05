# App name
APP = CaptureFrame
# Add any other object files to this list below
SRC_FILES= modules/Logger/Logger.cpp modules/Logger/LogStream.cpp CaptureFrame.cpp VirtualImage.cpp main.cpp
#SRC_FILES= modules/Logger/Logger.cpp modules/Logger/LogStream.cpp main.cpp

CFLAGS += -I$(INCLUDE)
LDLIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -ltensorflow-lite -ldl -lpthread

all: build

build: $(APP)

$(APP):
	$(CXX) -std=c++17 -o $@ $(SRC_FILES) $(LDFLAGS) $(LDLIBS) 
 
install: $(APP)
	cp $(APP) $(DESTDIR)/usr/bin
 
clean:
	rm -f $(APP) *.o
