#include <detpic32.h>


int main(void) {
    T3CONbits.TCKPS = 2;
    PR3 = 49999;
    TMR3 = 0;
    T3CONbits.TON = 1;

    OC1CONbits.OCM = 6;
    OC1CONbits.OCTSEL = 0;
    OC1RS = 10000;
    OC1CONbits.ON = 1;

    while(1);
    return 0;
}