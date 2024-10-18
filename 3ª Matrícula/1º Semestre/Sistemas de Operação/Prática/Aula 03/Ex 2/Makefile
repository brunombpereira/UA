CXX = g++
CXXFLAGS = -Wall -ggdb -pthread

TARGETS = main

HEADERS = process.h utils.h dbc.h

OBJS = process.o utils.o

.PHONY:	all clean cleanall

all: $(TARGETS)

main: main.o $(OBJS) $(HEADERS)
	$(CXX) -o $@ main.o $(OBJS) $(CXXFLAGS)

clean:
	rm -f *.o

cleanall:	clean
	rm -f $(TARGETS) 
