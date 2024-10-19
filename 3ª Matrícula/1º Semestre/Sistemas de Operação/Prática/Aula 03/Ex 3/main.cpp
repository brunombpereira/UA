#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include "process.h"


int main(void) {
    int* pcounter;

    int shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0600);

    if (shmid == -1)
    {
        printf("Error at shmid\n");
        exit(EXIT_FAILURE);
    }
    
    pcounter = (int*)shmat(shmid, NULL, 0);

    if (pcounter == (void*) -1)
    {
        printf("Error at shmat.");
        exit(EXIT_FAILURE);
    }

    *pcounter = 0;

    int semid = psemget(IPC_PRIVATE, 2, IPC_CREAT | 0600);

    while (*pcounter < 10 || *pcounter > 20)
    {
        printf("Insert a value between 10 and 20: ");
        scanf("%d", pcounter);
    }
    
    if (*pcounter % 2 == 0)
    {
        psem_up(semid, 0);
    } else
    {
        psem_up(semid, 1);
    }

    pid_t pid1 = pfork();
    
    if (pid1 == 0)
    {        
        while (*pcounter != 1)
        {
            if (*pcounter % 2 == 0)
            {
                psem_down(semid, 0);
                (*pcounter)--;
                printf("%u: %d\n", getpid(), *pcounter);
                psem_up(semid, 1);
            }
        }
        exit(EXIT_SUCCESS);                        
    }
    
    pid_t pid2 = pfork();
    
    if (pid2 == 0)
    {        
        while (*pcounter != 1)
        {
            if (*pcounter % 2 != 0)
            {
                psem_down(semid, 1);
                (*pcounter)--;
                printf("%u: %d\n", getpid(), *pcounter);
                psem_up(semid, 0);
            }
        }
        exit(EXIT_SUCCESS);                        
    }

    pwait(NULL);
    pwait(NULL);
    
    printf("PID 1: %u\n", pid1);
    printf("PID 2: %u\n", pid2);

    psemctl(semid, 1, IPC_RMID, NULL);
    pshmdt(pcounter);
    pshmctl(shmid, IPC_RMID, NULL);

    return EXIT_SUCCESS;
}