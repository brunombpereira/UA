#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#include "process.h"
#include "fifo.h"


void putRequestData(char* data, uint32_t id, Buffer pool[N]) {
    Buffer* buffer = &pool[id];
    
    strncpy(buffer->data, data, MAX_DATA_LENGTH-1);
    buffer->data[MAX_DATA_LENGTH-1] = '\0';
    buffer->status = 1;
}


void client(uint32_t id, Fifo* freeBuffers, Fifo* pendingRequests, Buffer pool[]) {
    char data[MAX_DATA_LENGTH];
    int response[3];
    Buffer request = getBuffer(freeBuffers);
    
    sprintf(data, "Request from client %d.", id);

    putRequestData(data, request.id, pool);

    fifoInsert(pendingRequests, pool[request.id]);

    while (pool[request.id].status != 2)
    {
        sleep(1);
    }
    
    for (int i = 0; i < 3; i++)
    {
        response[i] = pool[request.id].response[i];
    }
    
    printf("\nClient %d received response:\nChars = %d\nDigits = %d\nLetters = %d\n", id, response[0], response[1], response[2]);

    pool[request.id].status = 0;
    fifoInsert(freeBuffers, request);
}


void server(uint32_t id, Fifo* freeBuffers, Fifo* pendingRequests, Buffer pool[]) {
    char data[MAX_DATA_LENGTH];
    int numChar, numDigits = 0, numAlph = 0;

    Buffer request = getBuffer(pendingRequests);

    if (pool[request.id].data[0] == '\0') {
        printf("Server %d: Buffer %d está vazio ou não contém dados\n", id, request.id);
        return;
    }
    
    strncpy(data, request.data, MAX_DATA_LENGTH);

    printf("Server %d processing: %s\n", id, data);

    numChar = strlen(data);

    for (int i = 0; i < numChar; i++)
    {
        if (isdigit(data[i]))
        {
            numDigits++;
        } else if (isalpha(data[i]))
        {
            numAlph++;
        }        
    }
    
    pool[request.id].response[0] = numChar;
    pool[request.id].response[1] = numDigits;
    pool[request.id].response[2] = numAlph;
    pool[request.id].status = 2;    
}


int main(void) {
    uint32_t ns = 5;
    uint32_t nc = 5;

    int shmid = pshmget(IPC_PRIVATE, N*sizeof(Buffer) + 2*sizeof(Fifo), IPC_CREAT | 0600);

    if (shmid == -1)
    {
        printf("Error at shmid.");
        exit(EXIT_FAILURE);
    }

    void* sharedMemory = shmat(shmid, NULL, 0);

    if (sharedMemory == (void*)-1) {
        perror("Error at shmat");
        exit(EXIT_FAILURE);
    }

    char* shmBase = (char*)sharedMemory;
    
    Fifo* freeBuffers = (Fifo*)shmBase;
    Fifo* pendingRequests = (Fifo*)(shmBase + sizeof(Fifo));
    Buffer* pool = (Buffer*)(shmBase + 2 * sizeof(Fifo));

    fifoInit(freeBuffers);
    fifoInit(pendingRequests);

    for (uint32_t i = 0; i < N; i++)
    {
        pool[i].id = i;
        pool[i].status = 0;
        pool[i].data[0] = '\0';

        fifoInsert(freeBuffers, pool[i]);
    }
    

    pid_t cpid[nc];
    for (uint32_t i = 0; i < nc; i++)
    {
        if ((cpid[i] = pfork()) == 0)
        {
            client(i+1, freeBuffers, pendingRequests, pool);
            exit(EXIT_SUCCESS);
        }
    }
    
    pid_t spid[ns];
    for (uint32_t i = 0; i < ns; i++)
    {
        if ((spid[i] = pfork()) == 0)
        {
            server(i+1, freeBuffers, pendingRequests, pool);
            exit(EXIT_SUCCESS);
        }
    }

    for (uint32_t i = 0; i < ns; i++)
    {
        pwaitpid(spid[i], NULL, 0);
        printf("Server %u finished\n", i+1);
    }

    for (uint32_t i = 0; i < nc; i++)
    {
        pwaitpid(cpid[i], NULL, 0);
        printf("Client %u finished\n", i+1);
    }


    fifoDestroy(freeBuffers);
    fifoDestroy(pendingRequests);

    shmdt(freeBuffers);
    shmdt(pendingRequests);
    pshmctl(shmid, IPC_RMID, NULL);

    return 0;
}
