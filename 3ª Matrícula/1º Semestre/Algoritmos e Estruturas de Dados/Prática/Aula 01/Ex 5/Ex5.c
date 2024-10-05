#include <stdio.h>
#include <math.h>


int main(void) {
    int number_lines;

    printf("Quantas linhas tem a tabela? ");
    scanf("%d", &number_lines);

    printf("|  Número  |  Quadrado  | Raíz Quadrada |");

    for (int i = 0; i < number_lines; i++)
    {
        printf("\n ----------- ------------ ----------------");
        printf("\n|     %d     |      %d     |       %.2f      |", i, i*i, sqrt(i));
    }
    
    return 0;
}