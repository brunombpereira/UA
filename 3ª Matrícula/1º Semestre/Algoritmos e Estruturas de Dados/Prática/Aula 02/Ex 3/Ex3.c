#include <stdio.h>


void Permute(int* a, int* b, int* c);


int main(void) {
    int a = 1, b = 2, c = 3;

    printf("Antes da permutação: a = %d    b = %d    c = %d\n", a, b, c);

	Permute(&a, &b, &c);

	printf("Depois da permutação: a = %d    b = %d    c = %d", a, b, c);

	return 0;
}


void Permute(int* a, int* b, int* c) {
	int temp = *c;
	*c = *b;
	*b = *a;
	*a = temp;
}