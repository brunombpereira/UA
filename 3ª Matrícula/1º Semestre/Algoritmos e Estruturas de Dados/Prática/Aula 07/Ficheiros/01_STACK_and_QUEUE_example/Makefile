CXX = gcc
CFLAGS=-Wall

OBJS= 01_example.c IntegersStack.o IntegersQueue.o

TARGET = 01_example

.PHONY:	all clean cleanall

all:	$(TARGET) 

01_example: $(OBJS)
	$(CXX) $(CFLAGS) -o $@ $^

clean:
	rm -fv *.o core

cleanall: clean
	rm -f $(TARGET)

