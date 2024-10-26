#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <libgen.h>
#include <stdlib.h>
#include <string.h>

#include "fifo.h"
#include "thread.h"

void fifoInit(Fifo *f)
{
    /* init fifo */
    f->in = f->out = 0;
    f->count = 0;
    memset(f->id, 0x0, N*sizeof(uint32_t));
    
    /* init conditions variables */
    cond_init(&f->notFull, NULL);
    cond_init(&f->notEmpty, NULL);

    /* init access mutex */
    mutex_init(&f->access, NULL);
}

static bool fifoIsFull(Fifo *f)
{
    return f->count == N;
}

static bool fifoIsEmpty(Fifo *f)
{
    return f->count == 0;
}

void fifoInsert(Fifo *f, uint32_t id)
{
    /* lock access on entry */
    mutex_lock(&f->access);

    /* wait until fifo is not full */
    while (fifoIsFull(f))
    {
        cond_wait(&f->notFull, &f->access);
    }

    /* make insertion */
    f->id[f->in] = id;
    f->in = (f->in + 1) % N;
    f->count++;

    /* signal fifo is not empty */
    cond_broadcast(&f->notEmpty);

    /* unlock access before quitting */
    mutex_unlock(&f->access);
}

uint32_t fifoRetrieve(Fifo *f)
{
    /* lock access on entry */
    mutex_lock(&f->access);

    /* wait until fifo is not empty */
    while (fifoIsEmpty(f))
    {
        cond_wait(&f->notEmpty, &f->access);
    }

    /* memorize item to be returned */
    uint32_t id = f->id[f->out];

    /* update fifo */
    f->out = (f->out + 1) % N;
    f->count--;

    /* signal fifo is not empty */
    cond_broadcast(&f->notFull);

    /* unlock access before quitting */
    mutex_unlock(&f->access);

    /* return item */
    return id;
}

void fifoDestroy(Fifo *f)
{
    cond_destroy(&f->notFull);
    cond_destroy(&f->notEmpty);
    mutex_destroy(&f->access);
    f->count = 0;
    f->in = f->out = 0;
}
