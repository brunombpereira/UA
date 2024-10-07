#include <stdio.h>
#include <assert.h>
#include <stdlib.h>


double* readArray(size_t* size_p);
void displayArray(double* a, size_t n);
double* append(double* array_1, size_t size_1, double* array_2, size_t size_2);


int main(void) {
    size_t n_a, n_b;

    printf("Número de elementos do primeiro array: ");
    scanf("%llu", &n_a);
    assert(n_a > 0);
    assert(&n_a != NULL);
    double* a = readArray(&n_a);

    printf("\nNúmero de elementos do segundo array: ");
    scanf("%llu", &n_b);
    assert(n_b > 0);
    assert(&n_b != NULL);
    double* b = readArray(&n_b);

    assert(a != NULL);
    displayArray(a, n_a);
    assert(b != NULL);
    displayArray(b, n_b);

    double* c = append(a, n_a, b, n_b);
    assert(c != NULL);
    displayArray(c, (n_a + n_b));

    free(a);
    free(b);
    free(c);
    return 0;
}


double* readArray(size_t* size_p) {
    double* c = (double*)malloc(*size_p * sizeof(double));

    if (c == NULL)
    {
        return NULL;
        *size_p = 0;
    }
    
    for (size_t i = 0; i < *size_p; i++)
    {
        printf("%lld elemento: ", i+1);
        scanf("%lf", &c[i]);
    }
    
    return c;
}


void displayArray(double* a, size_t n) {
    printf("Array = [ ");

    for (size_t i = 0; i < n; i++)
    {
        if (i != n-1)
        {
            printf("%.2lf, ", a[i]);
        } else
        {
            printf("%.2lf ", a[i]);
        }
    }

    printf("]\n");
}


double* append(double* array_1, size_t size_1, double* array_2, size_t size_2) {
    size_t n_c = size_1 + size_2;

    double* d = (double*)malloc(n_c * sizeof(double));

    if (d == NULL)
    {
        return NULL;
    }
    

    for (size_t i = 0; i < size_1; i++)
    {
        d[i] = array_1[i];
    }

    for (size_t i = 0; i < size_2; i++)
    {
        d[size_1 + i] = array_2[i];
    }
    
    return d;    
}