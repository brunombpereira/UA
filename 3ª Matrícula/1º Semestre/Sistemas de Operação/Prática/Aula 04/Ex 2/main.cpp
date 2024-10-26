#include <stdio.h>
#include <stdlib.h>

#include "thread.h"
#include "fifo.h"
#include "utils.h"


static uint32_t N1 = 0;


void* child(void* arg) {
    uint32_t N2 = 0;

    while (N2 < 10 || N2 > 20)
    {
        printf("Insert a number between 10 and 20: ");
        scanf("%d", &N2);
    }

    while (N1 != N2)
    {
        printf("N1: %d\n", N1);
        N1++;
    }
    thread_exit(NULL);
    return NULL;
}


int main(void) {
    while (N1 < 1 || N1 > 9)
    {
        printf("Insert a number between 1 and 9: ");
        scanf("%d", &N1);
    }

    pthread_t chilThread;
    thread_create(&chilThread, NULL, child, 0);

    thread_join(chilThread, NULL);

    while (N1 != 1)
    {
        printf("N1: %d\n", N1);
        N1--;
    }
    printf("N1: %d\n", N1);

    return 0;
}