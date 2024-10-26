/*
 * Definition of the FIFO data type and manipulating functions
 *
 * The fifo is defined for a maximum capacity of N items
 */

#ifndef __SO_FSO_2425_IPC_FIFO__
#define __SO_FSO_2425_IPC_FIFO__

#include <stdint.h>
#include <stdlib.h>

#include "thread.h"

#define N 200


struct Fifo
{
    uint32_t count;
    uint32_t in, out;
    uint32_t id[N];

    pthread_mutex_t access;
    pthread_cond_t notFull, notEmpty;
};

void fifoInit(Fifo *f);

void fifoInsert(Fifo *f, uint32_t id);

uint32_t fifoRetrieve(Fifo *f);

void fifoDestroy(Fifo *f);

#endif // __SO_FSO_2425_IPC_FIFO__

