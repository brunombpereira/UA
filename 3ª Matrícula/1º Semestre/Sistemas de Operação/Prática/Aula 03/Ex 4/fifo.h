/*
 * Definition of the FIFO data type and manipulating functions
 *
 * The fifo is defined for a maximum capacity of N items
 */

#ifndef __SO_FSO_2425_IPC_FIFO__
#define __SO_FSO_2425_IPC_FIFO__

#include <stdint.h>
#include <stdlib.h>

#define N 200
#define MAX_DATA_LENGTH 256

struct Buffer
{ 
    uint32_t id;
    char data[MAX_DATA_LENGTH];
    int response[3];
    int status;
};

struct Fifo
{
    uint32_t count;
    uint32_t in, out;
    Buffer buffers[N];
    int sem;
};

void fifoInit(Fifo *f);

bool fifoIsFull(Fifo *f);

bool fifoIsEmpty(Fifo *f);

void fifoInsert(Fifo *f, Buffer buffer);

Buffer getBuffer(Fifo *f);

void fifoDestroy(Fifo *f);

#endif // __SO_FSO_2425_IPC_FIFO__

