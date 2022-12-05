# App name
APP = Logger
# Add any other object files to this list below
SRC_FILES= LogStream.cpp Logger.cpp main.cpp
#SRC_FILES= main.cpp 

CFLAGS += -I$(INCLUDE)
LDLIBS += -lpthread

all: build

build: $(APP)

$(APP):
	$(CXX) -std=c++17 -o $@ $(SRC_FILES) $(LDFLAGS) $(LDLIBS) 
 
install: $(APP)
	cp $(APP) $(DESTDIR)/usr/bin
 
clean:
	rm -f $(APP) *.o
