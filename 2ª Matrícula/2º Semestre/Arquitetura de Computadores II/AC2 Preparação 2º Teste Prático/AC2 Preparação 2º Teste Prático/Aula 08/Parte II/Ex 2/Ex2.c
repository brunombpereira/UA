#include <detpic32.h>


int main(void) {
    TRISDbits.TRISD8 = 1;
    TRISEbits.TRISE0 = 0;
    LATEbits.LATE0 = 0;

    T2CONbits.TCKPS = 7;
    PR2 = 26041;
    TMR2 = 0;
    T2CONbits.TON = 1;

    IPC2bits.T2IP = 2;
    IEC0bits.T2IE = 1;
    IFS0bits.T2IF = 0;

    INTCON.INT1EP = 0;

    EnableInterrupts();

    while(1);
    return 0;
}


void _int_(8) isr_T2(void) {
    LATEbits.LATE0 = 1;
    delay(3000);
    LATEbits.LATE0 = 0;

    IFS0bits.T2IF = 0;
}


void _int_(7) isr_INT1(void) {
    LATEbits.LATE0 = 1;
    delay(3000);
    LATEbits.LATE0 = 0;

    INTCON.INT1EP = 0;
}