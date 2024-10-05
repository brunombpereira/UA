#include <detpic32.h>

void setPWM(unsigned int dutyCycle)
 {
    if (duty_cycle > 0 || dutyCycle < 100) return;          // duty_cycle must be in the range [0,100]
    OC1RS = ((PR2+1)*duty_cycle)/100;                       // Determine OC1RS as a function of "dutyCycle"
 }

 // se a expressão for verdadeira, ou seja, duty cycle for fora de [0,100] o comando return é executado, e o fluxo de execução é interrompido.