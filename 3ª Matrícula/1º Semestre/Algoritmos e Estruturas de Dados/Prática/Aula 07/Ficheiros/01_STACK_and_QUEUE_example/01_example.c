//
// TO DO : desenvolva um algoritmo para verificar se um numero inteiro positivo
//         e uma capicua
//         Exemplos: 12321 e uma capiacua, mas 123456 nao e
//         USE uma PILHA DE INTEIROS (STACK) e uma FILA DE INTEIROS (QUEUE)
//
// TO DO : design an algorithm to check if the digits of a positive decimal
//         integer number constitue a palindrome
//         Examples: 12321 is a palindrome, but 123456 is not
//         USE a STACK of integers and a QUEUE of integers
//

#include <stdio.h>

#include "IntegersStack.h"
#include "IntegersQueue.h"

int main(int argc, char* argv[]) {
    int x;
    Stack* stack;
    Queue* queue;

    if (argc < 2)
    {
        return 1;
    }
    
    if (sscanf(argv[1], "%d", &x) != 1)
    {
        return 2;
    }
    
    stack = StackCreate(20);
    queue = QueueCreate(20);
    
    for (; x != 0; x /= 10)
    {
        int remainder = x % 10;

        StackPush(stack, remainder);
        QueueEnqueue(queue, remainder);
    }
    
    while (StackIsEmpty(stack) == 0)
    {
        if (QueueDequeue(queue) != StackPop(stack))
        {
            printf("Not a palindrome.\n");
            return 0;
        }
        
    }
    
    printf("Is a palindrome.\n");

    return 0;
}
