#include <stdio.h>


int main(void) {
    int array[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    size_t len = sizeof(array) / sizeof(array[0]);
    unsigned int cnt = 0, comparisons = 0;
/*
    for (int i = 0; i < len -1; i++)
    {
        comparisons++;
        if (array[i] == array[i-1] + array[i+1])
        {
            cnt++;                                          // Função menos eficiente
        }
    }
    
    printf("Counter = %u\n", cnt);
*/
    int prev, prev_prev;

    prev = array[1];
    prev_prev = array[0];

    for (int i = 2; i < len; i++)
    {
        int sub = prev - prev_prev;
        prev_prev = prev;
        prev = array[i];

        comparisons++;
        if (prev == sub)
        {
            cnt++;
        }        
    }
    
    printf("Counter = %u\nComparações = %u\n", cnt, comparisons);

    return 0;
}