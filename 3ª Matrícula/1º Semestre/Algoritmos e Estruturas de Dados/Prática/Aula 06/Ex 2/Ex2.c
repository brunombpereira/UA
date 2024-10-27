#include <stdio.h>


#define MAX 10


int d_mem[MAX+1] = {0};


int max(int a, int b) {
    if (a > b)
    {
        return a;
    }
    return b;
}


int solucaoOtimaRec(int array[], int n) {
    if (n == 0)
    {
        return 0;
    } else if (n == 1)
    {
        return array[n-1];
    }
    
    return max(array[n-1] + solucaoOtimaRec(array, n-2), solucaoOtimaRec(array, n-1));
}


int solucaoOtimaInt(int array[], int n) {
    int d[n];

    if (n == 0)
    {
        return 0;
    } else if (n == 1)
    {
        return array[n-1];
    }
    
    d[0] = array[0];
    d[1] = max(array[0], array[1]);

    for (int i = 2; i < n; i++)
    {
        d[i] = max(array[i] + d[i-2], d[i-1]);
    }
    
    return d[n-1];
}


int solucaoOtimaMem(int array[], int n) {
    if (n == 0)
    {
        return 0;
    } else if (n == 1)
    {
        return array[n-1];
    }
    
    if (d_mem[n] != 0)
    {
        return d_mem[n];
    }
    
    d_mem[n] = max(array[n-1] + solucaoOtimaRec(array, n-2), solucaoOtimaRec(array, n-1));

    return d_mem[n];
}


int main(void) {
    int array[] = {5, 1, 2, 10, 6, 2};
    int lenght = sizeof(array) / sizeof(array[0]);

    printf("O valor da solução ótima recursiva é: %d\n", solucaoOtimaRec(array, lenght));
    printf("O valor da solução ótima interativa é: %d\n", solucaoOtimaInt(array, lenght));
    printf("O valor da solução ótima memoization é: %d\n", solucaoOtimaMem(array, lenght));
}