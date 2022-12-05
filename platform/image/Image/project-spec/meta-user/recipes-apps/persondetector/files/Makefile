APP = myDetector
SRC_FILES= main.cpp Detector.cpp VirtualImage.cpp PhyImage.cpp


CFLAGS += -I$(INCLUDE)
LDLIBS += -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_imgcodecs -ltensorflow-lite -ldl -lpthread

all: build

build: $(APP)

$(APP):
	$(CXX) -std=c++14 -o $@ $(SRC_FILES) $(LDFLAGS) $(LDLIBS) 
 
install: $(APP)
	cp $(APP) $(DESTDIR)/usr/bin
 
clean:
	rm -f $(APP) *.o
