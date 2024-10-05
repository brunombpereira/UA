#include <detpic32.h>


void delay(unsigned int ms);


volatile int cnt = 0;


int main(void) {
    TRISEbits.TRISE0 = 0;
    LATEbits.LATE0 = 0;

    T2CONbits.TCKPS = 7;
    PR2 = 78125;
    TMR2 = 0;
    T2CONbits.TON = 1;

    IPC2bits.T2IP = 2;
    IEC0bits.T2IE = 1;
    IFS0bits.T2IF = 0;

    IPC1bits.INT1IP = 2;
    IEC0bits.INT1IE = 1;
    IFS0bits.INT1IF = 0;
    INTCONbits.INT1EP = 0;

    EnableInterrupts();

    while(1);
    return 0;
}


void _int_(8) isr_T2(void) {
    if (cnt == 1)
    {
        LATEbits.LATE0 = 1;
        delay(3000);
        LATEbits.LATE0 = 0;
        cnt = 0;
    } else {
        cnt ++;
    }

    IFS0bits.T2IF = 0;
} 


void _int_(7) isr_INT1(void) {
    LATEbits.LATE0 = 1;
    delay(3000);
    LATEbits.LATE0 = 0;

    INTCONbits.INT1EP = 0;
    IFS0bits.INT1IF = 0;
}


void delay(unsigned int ms) {
    int k = 20000 * ms;
    resetCoreTimer();
    while(readCoreTimer() < k);
}