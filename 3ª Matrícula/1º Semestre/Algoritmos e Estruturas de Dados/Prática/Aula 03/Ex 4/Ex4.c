#include <stdio.h>
#include <math.h>


#define base 10


int main(void) {
    int number[7] = {0, 0, 0, 0, 0, 0, 0}, sum = 0, fatorial, factoriao[5] = {-1, -1, -1, -1, -1};

    for (int i = 0; i < pow(base,6); i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (number[j] != 0)
            {
                for (int g = j; g < 6; g++)
                {
                    if (number[g] == 0)
                    {
                        fatorial = 1;
                    } else {
                        fatorial = 1;
                        for (int h = 1; h < number[g] + 1; h++)
                        {
                            fatorial = fatorial * h;
                        }
                    }
                    sum += fatorial;
                }
                break; 
            }                   
        }
        
        if (number[6] == 0)
        {
            fatorial = 1;
        } else {
            fatorial = 1;
            for (int h = 1; h < number[6] + 1; h++)
            {
                fatorial = fatorial * h;
            }
        }
        sum += fatorial;

        if (i == sum)
        {
            for (int j = 0; j < 5; j++)
            {
                if (factoriao[j] == -1)
                {
                    factoriao[j] = i;
                    break;
                }
            }
        }
        
        for (int j = 6; j >= 0; j--)
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

    for (int i = 0; i < 5; i++)
    {
        if (factoriao[i] != -1)
        {
            printf("%d\n", factoriao[i]);
        }
    }
    
    return 0;
}