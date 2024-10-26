#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#include "utils.h"
#include "thread.h"


static uint32_t value;

pthread_mutex_t access;
pthread_cond_t par, impar;


void* child(void* arg) {
    uint32_t index = *(uint32_t*)arg;

    pthread_mutex_lock(&access);

    while (value > 1)
    {
        if (value % 2 != index)
        {
            if (index == 0)
            {
                pthread_cond_wait(&par, &access);
            } else {
                pthread_cond_wait(&impar, &access);
            }
        } 
                
        printf("Value: %d (%lu)\n", value, pthread_self());        
        value--;

        if (value % 2 == 0)
        {
            pthread_cond_signal(&par);
        } else {
            pthread_cond_signal(&impar);
        }
    }
    pthread_mutex_unlock(&access);
    return NULL;
}


int main(void) {
    uint32_t nc = 2;
    int number = 0;

    pthread_cond_init(&par, NULL);
    pthread_cond_init(&impar, NULL);

    pthread_mutex_init(&access, NULL);

    while (number < 10 || number > 20)
    {
        printf("Insert a value between 10 and 20: ");
        scanf("%d", &number);
    }

    value = number;


    pthread_t cthr[nc];
    for (uint32_t i = 0; i < nc; i++)
    {
        uint32_t* index = (uint32_t*)malloc(sizeof(uint32_t));
        *index = i;
        thread_create(&cthr[i], NULL, child, (void*)index);
    }
    
    for (uint32_t i = 0; i < nc; i++)
    {
        thread_join(cthr[i], NULL);
    }
    
    pthread_cond_destroy(&par);
    pthread_cond_destroy(&impar);
    pthread_mutex_destroy(&access);

    return 0;
}