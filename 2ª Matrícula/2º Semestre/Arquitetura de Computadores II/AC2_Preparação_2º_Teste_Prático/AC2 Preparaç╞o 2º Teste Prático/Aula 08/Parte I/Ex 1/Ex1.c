#include <detpic32.h>


int main(void) {
    // Configuração do timer T3:
    T3CONbits.TCKPS = 7;                // 1:256 prescaler
    PR3 = 39062;                        // PR3 = ((20 000 000 / Kpresc) / fout) - 1
    TMR3 = 0;                           // Clear timer T3 count register
    T3CONbits.TON = 1;                  // Enable timer T3 (must be the last command of the timer configuration sequence)

    while (1)
    {
        while(IFS0bits.T3IF == 0);      // Wait while T3IF = 0
        IFS0bits.T3IF = 0;              // Reset T3IF
        putChar('.');
    }
    return 0;
}