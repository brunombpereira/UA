#include <detpic32.h>

// Notas da aula:
// Para um dado fout:
// 1 - calcular o Kprescaler
// 2 - calcular a freq. á entrada do TMRx
// 3 - Dividir o fout pela freq. á entrada do TMRx - 1
// 4 - Programar o PRx com o valor de 3
// 5 - Enable do TIMER

int main(void)
{

    T3CONbits.TCKPS = 7;        // fout_presc = 78 KHz)
    PR3 = 39062;                // PR3 = (78125 Hz /2)-1 = 39061.5
    TMR3 = 0;                   // Clear timer T3 count register
    T3CONbits.TON = 1;          // Configure Timer T3 (2 Hz with interrupts disabled)
    
    while(1)
    {   // ciclo de polling
        while(IFS0bits.T3IF == 0 );  // Wait while T3IF = 0
        IFS0bits.T3IF = 0;           // Reset T3IF
        putChar('.');
    }
    return 0;
}
