#include <stdio.h>
#include <stdlib.h>

#include "process.h"


int main(void) {
    int *pcounter;
    int shmid = pshmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0600);

    if (shmid == -1) {
        perror("pshmget failed");
        exit(EXIT_FAILURE);
    }

    pcounter = (int *)shmat(shmid, NULL, 0);

    if (pcounter == (void *) -1) {
        perror("shmat failed");
        exit(EXIT_FAILURE);
    }

    *pcounter = 1;

    if (pfork() != 0)
    {
        pwait(NULL);

        while (*pcounter != 1)
        {
            (*pcounter)--;
            printf("%d ", *pcounter);
        }
        printf("\n");
    } else
    {
        int value = 0;

        while (value < 10 || value > 20)
        {
            printf("Insert a number between 10 and 20: ");
            scanf("%d", &value);
        }

        printf("%d ", *pcounter);

        while (*pcounter != value)
        {
            (*pcounter)++;
            printf("%d ", *pcounter);
        }

        exit(EXIT_SUCCESS);
    }
    
    pshmdt(pcounter);
    pshmctl(shmid, IPC_RMID, NULL);

    return EXIT_SUCCESS;
}