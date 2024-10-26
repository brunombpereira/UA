CXX = g++
CXXFLAGS = -Wall -ggdb -pthread

TARGETS = msin

OBJS = thread.o utils.o

.PHONY:	all clean cleanall

all: $(TARGETS)

main: main.o fifo.o $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS)

*.o:	*.h

clean:
	rm -f *.o

cleanall:	clean
	rm -f $(TARGETS) 
