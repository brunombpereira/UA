#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>


void displayPol(double* coef, size_t degree);
double computePol(double* coef, size_t degree, double x);
unsigned int getRealRoots(double* coef, size_t degree, double* root_1, double* root_2);


int main(void) {
    size_t degree;
    double x, result;
    double root_1, root_2;

    printf("Grau do polinómio: ");
    scanf("%lld", &degree);

    assert(degree >= 0);
    
    double* pol = (double*)malloc(degree * sizeof(double));

    printf("Indique os coeficientes do polinómio:\n");

    for (size_t i = 0; i < degree+1; i++)
    {
        printf("%lld coeficiente: ", i+1);
        scanf("%lf", &pol[i]);
    }
    
    assert(pol != NULL);
    displayPol(pol, degree);

    printf("Valor de x: ");
    scanf("%lf", &x);

    result = computePol(pol, degree, x);

    printf("Pol(%lf) = %lf\n", x, result);

    unsigned int realRoot = getRealRoots(pol,degree,&root_1,&root_2);
    
    if (realRoot == 0)
    {
        printf("No real roots.\n");
    } else if (realRoot == 1)
    {
        printf("1 real root with multiplicity 2.\nRoot: %lf", root_1);
    } else if (realRoot == 2)
    {
        printf("2 distinct real roots.\nRoot 1: %lf\nRoot 2: %lf\n", root_1, root_2);
    }
    
    return 0;
}


void displayPol(double* coef, size_t degree) {
    printf("Pol(X) = ");

    for (size_t i = 0; i < degree+1; i++)
    {
        if (i != degree)
        {
            printf("%lf * x^%lld + ", coef[i], degree-i);
        } else {
            printf("%lf\n", coef[i]);
        }
    }
}


double computePol(double* coef, size_t degree, double x) {
    double result;

    for (size_t i = 0; i < degree+1; i++)
    {
        result += coef[i] * pow(x,degree-i);
    }
    
    return result;
}


unsigned int getRealRoots(double* coef, size_t degree, double* root_1, double* root_2) {
    assert(degree == 2 && coef[0] != 0 && root_1 != NULL && root_2 != NULL);
    double alpha = pow(coef[1], 2) - (4 * coef[0] * coef[2]);

    if (alpha < 0)
    {
        *root_1 = 0.0;
        *root_2 = 0.0;
        return 0;   
    }
    
    *root_1 = (-coef[1] - sqrt(alpha)) / (2 * coef[0]);
    *root_2 = (-coef[1] + sqrt(alpha)) / (2 * coef[0]);

    if (*root_1 == *root_2)
    {
        return 1;
    } else {
        return 2;
    }    
}