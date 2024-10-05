#include <stdio.h>


int main(void) {
    printf("sizeof(void *)......%lld", sizeof(void *));
    printf("\nsizeof(void)........%lld", sizeof(void));
    printf("\nsizeof(char)........%lld", sizeof(char));
    printf("\nsizeof(short).......%lld", sizeof(short));
    printf("\nsizeof(int).........%lld", sizeof(int));
    printf("\nsizeof(long)........%lld", sizeof(long));
    printf("\nsizeof(long long)...%lld", sizeof(long long));
    printf("\nsizeof(float).......%lld", sizeof(float));
    printf("\nsizeof(double)......%lld", sizeof(double));

    return 0;
}