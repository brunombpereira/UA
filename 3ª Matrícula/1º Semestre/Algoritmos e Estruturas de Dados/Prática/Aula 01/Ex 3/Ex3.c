#include <stdio.h>


int main(void) {
    char name[100];
    char surname[100];

    printf("Nome próprio: ");
    scanf("%s", name);
    printf("Apelido: ");
    scanf("%s", surname);

    printf("Hello %s %s", name, surname);

    return 0;
}