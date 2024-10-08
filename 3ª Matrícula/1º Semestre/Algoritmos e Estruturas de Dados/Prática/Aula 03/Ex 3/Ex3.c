#include <stdio.h>
#include <math.h>


#define N 3
#define base 10


int main(void) {
    int number[N], sum = 0, armstrong[9] = {-1, -1, -1, -1, -1, -1, -1, -1, -1};

    number[0] = 1;
    for (int i = 1; i < N; i++)
    {        
        number[i] = 0;
    }
    

    for (int i = pow(base,(N-1)); i < (pow(base,N) - 1); i++)
    {
        for (int j = 0; j < N; j++)
        {
            sum += pow(number[j],N);
        }
        
        if (sum == i)
        {
            for (int j = 0; j < 9; j++)
            {
                if (armstrong[j] == -1)
                {
                    armstrong[j] = i;
                    break;
                }
            }
        }
        
        for (int j = N-1; j >= 0; j--)
        {
            if (number[j] < 9)
            {
                number[j]++;
                break;
            }
            number[j] = 0;
        }

        sum = 0;
    }

    for (int i = 0; i < 9; i++)
    {
        if (armstrong[i] != -1)
        {
            printf("%d\n", armstrong[i]);
        }
        
    }
    
    return 0;
}