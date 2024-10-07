#include <stdio.h>
#include <assert.h>


void DisplayArray(double* a, size_t n);
double* ReadArray(size_t* size_p);
double* Append(double* array_1, size_t size_1, double* array_2, size_t size_2);


int main(void) {
    double array_1[] = {1.00, 2.00, 3.00};
    double array_2[] = {4.00, 5.00, 6.00, 7.00};

    size_t arr1 = sizeof(array_1);
    size_t arr2 = sizeof(array_2);

    DisplayArray(&array_1, arr1);
    DisplayArray(&array_2, arr2);
}