#include <stdio.h>


int main(void) {
    int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    size_t len = sizeof(array) / sizeof(array[0]);
    int cnt = 0, cost = 0;

    for (int i = 0; i < len - 2; i++)
    {
        int array_i = array[i];

        for (int j = i + 1; j < len - 1; j++)
        {
            int array_j = array[j];

            for (int k = j + 1; k < len; k++)
            {
                cost++;
                if (array[k] == array_i + array_j)
                {
                    cnt++;
                }
            }
        }
    }
    
    printf("Counter = %d\nCost = %d\n", cnt, cost);

    return 0;
}