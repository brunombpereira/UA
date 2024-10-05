#include <stdio.h>


void printArray(char s[], int a[], int lenght);
void cumSum(int a[], int b[], int lenght);

int main(void) {
    int a[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int b[12];

    int lenght = sizeof(a) / sizeof(a[0]);

    printArray("a:\n", a, lenght);

    cumSum(a,b,lenght);
    printArray("\nb:\n", b, 12);

    return 0;
}


void printArray(char s[], int a[], int lenght) {
    printf("%s", s);
    for (int i = 0; i < lenght; i++)
    {
        printf("%d ", a[i]);
    }
}


void cumSum(int a[], int b[], int lenght) {
    int c = 0;

    for (int i = 0; i < lenght; i++)
    {
        c += a[i];
        b[i] = c;
    }
}