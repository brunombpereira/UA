#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <math.h>
#include <libgen.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "utils.h"
#include "thread.h"
#include "fifo.h"


pthread_mutex_t status;
pthread_cond_t clear, request;


struct Buffer
{
    uint32_t id, numChar, numDig, numAlph;
    char str[250];
};


static Fifo* freeBuffers = NULL;
static Fifo* pendingRequests = NULL;
static Buffer* pool[N];


void processResponse(uint32_t bufferId) {
    uint32_t numDig = 0, numAlph = 0;

    for (uint32_t i = 0; i < strlen(pool[bufferId]->str); i++)
    {
        if (isalpha(pool[bufferId]->str[i]))
        {
            numAlph++;
        } else if (isdigit(pool[bufferId]->str[i]))
        {
            numDig++;
        }   
    }
    
    pool[bufferId]->numAlph = numAlph;
    pool[bufferId]->numDig = numDig;
    pool[bufferId]->numChar = strlen(pool[bufferId]->str);
}


void* producerThread(void* arg) {
    uint32_t bufferId = fifoRetrieve(pendingRequests);
    processResponse(bufferId);
    pthread_cond_signal(&request);

    pthread_exit(NULL);
    return NULL;
}


void* consumerThread(void* arg) {
    uint32_t ncId = *(uint32_t*)arg;
    char response[250];

    sprintf(response, "Request from client %u", ncId);
    
    pthread_mutex_lock(&status);

    uint32_t bufferId = fifoRetrieve(freeBuffers);    

    strcpy(pool[bufferId]->str, response);

    fifoInsert(pendingRequests, bufferId);

    pthread_cond_wait(&request, &status);

    printf("\nNumber of Characters: %u\nNumber of Digits: %u\nNumber of Letters: %u", pool[bufferId]->numChar, pool[bufferId]->numDig, pool[bufferId]->numAlph);

    pool[bufferId]->numChar = 0;
    pool[bufferId]->numDig = 0;
    pool[bufferId]->numAlph = 0;
    pool[bufferId]->str[0] = '\0';

    fifoInsert(freeBuffers, bufferId);

    pthread_cond_broadcast(&clear);
    pthread_mutex_unlock(&status);
    return NULL;
}


int main (int argc, char *argv[])
{
    uint32_t np = 5;
    uint32_t nc = 5;

    freeBuffers = (Fifo*)mem_alloc(sizeof(Fifo));
    pendingRequests = (Fifo*)mem_alloc(sizeof(Fifo));
    
    fifoInit(freeBuffers);
    fifoInit(pendingRequests);

    for (int i = 0; i < N; i++)
    {
        pool[i] = (Buffer*)malloc(sizeof(Buffer));
        pool[i]->id = i;
        pool[i]->numAlph = pool[i]->numChar = pool[i]->numDig = 0;
        pool[i]->str[0] = '\0';

        fifoInsert(freeBuffers, i);
    }
    
    pthread_cond_init(&clear, NULL);
    pthread_cond_init(&request, NULL);

    pthread_mutex_init(&status, NULL);

    /* launching child threads to play as consumers */
    pthread_t cthr[nc];
    for (uint32_t i = 0; i < nc; i++)
    {
        uint32_t* arg = (uint32_t*)malloc(sizeof(uint32_t));
        *arg = i;
        pthread_create(&cthr[i], NULL, consumerThread, arg);
    }

    /* launching child processes to play as producers */
    pthread_t pthr[np];
    for (uint32_t i = 0; i < np; i++)
    {
        pthread_create(&pthr[i], NULL, producerThread, NULL);
    }

    /* wait for producers to finish */
    for (uint32_t i = 0; i < np; i++)
    {
        pthread_join(pthr[i], NULL);
        printf("\nProducer %u finished\n", i+1);
    }
    
    /* wait for consumers to finish */
    for (uint32_t i = 0; i < nc; i++)
    {
        pthread_join(cthr[i], NULL);
        printf("\nConsumer %u finished\n", i+1);
    }

    pthread_cond_destroy(&clear);
    pthread_cond_destroy(&request);
    pthread_mutex_destroy(&status);

    for (int i = 0; i < N; i++) {
        free(pool[i]);
    }
    
    fifoDestroy(freeBuffers);
    fifoDestroy(pendingRequests);

    return 0;
}

