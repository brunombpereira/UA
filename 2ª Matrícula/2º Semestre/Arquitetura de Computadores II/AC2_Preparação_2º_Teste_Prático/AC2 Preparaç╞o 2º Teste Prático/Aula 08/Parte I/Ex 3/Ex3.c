#include <detpic32.h>


volatile int cnt = 0;

int main(void) {
    // Configuração do timer T3:
    T3CONbits.TCKPS = 7;                // 1:256 prescaler
    PR3 = 39062;                        // PR3 = ((20 000 000 / Kpresc) / fout) - 1
    TMR3 = 0;                           // Clear timer T3 count register
    T3CONbits.TON = 1;                  // Enable timer T3 (must be the last command of the timer configuration sequence)

    // Configuração do timer para gerar interrupções:
    IPC3bits.T3IP = 2;                  // Interrupt priority (must be in range [1..6])
    IEC0bits.T3IE = 1;                  // Enable timer T3 interrupts
    IFS0bits.T3IF = 0;                  // Reset timer T3 interrupt flag
    EnableInterrupts();

    while (1);
    return 0;
}


void _int_(12) isr_T3(void) {
    if (cnt == 1)
    {   
        putChar('.');
        int cnt = 0;
    } else {
        cnt ++;
    }
    
    IFS0bits.T3IF = 0;
}