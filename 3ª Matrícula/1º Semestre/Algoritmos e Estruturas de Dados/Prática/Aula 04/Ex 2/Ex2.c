#include <stdio.h>


int main(void) {
    double array[] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512};
    double prev = array[1];
    double r = prev / array[0];
    size_t len = sizeof(array) / sizeof(array[0]);
    int valid = 1, cost = 1;

    for (int i = 2; i < len; i++)
    {
        cost++;
        prev *= r;
        if (array[i] != prev)
        {
            valid = 0;
            break;
        }
    }
    
    if (valid == 1)
    {
        printf("Valid sequence.\nCost = %d\n", cost);
    } else {
        printf("Non-valid sequence.\nCost = %d\n", cost);
    }
    
    return 0;
}