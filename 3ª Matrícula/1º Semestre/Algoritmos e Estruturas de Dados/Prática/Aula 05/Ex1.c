#include <stdio.h>


#define n 15


int f1(int n) {
    if (n == 1)
    {
        return 1;
    }
    
    return f1(n/2) + n;
}


int f2(int n) {
    if (n == 1)
    {
        return 1;
    }
    
    return f2(n/2) + f2((n+1)/2) + n;
}


int f3(int n) {
    if (n == 1)
    {
        return 1;
    } else if ((n % 2) != 0)
    {
        return f3(n/2) + f3((n+1)/2) + n;
    }
    
    return 2 * f3(n/2) + n;
}