all: helloworld
 
src=helloworld.cpp
 
CFLAGS = -I$(INCLUDE)
 
OBJ = $(SRC:.cpp=.o)

helloworld: helloworld.o
	$(CXX) $(LDFLAGS) -o $@ helloworld.o $(LDLIBS)
 
install: helloworld
	cp helloworld $(DESTDIR)/usr/bin
 
clean:
	rm -f helloworld *.o