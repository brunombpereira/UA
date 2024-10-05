#include <detpic32.h>


void setPWM(unsigned int dutyCicle);


int main(void) {
    unsigned int dutyCicle = 25;

    TRISDbits.TRISD0 = 1;
    TRISCbits.TRISC14 = 1;

    T3CONbits.TCKPS = 2;
    PR3 = 49999;
    TMR3 = 0;
    T3CONbits.TON = 1;

    OC1CONbits.OCM = 6;
    OC1CONbits.OCTSEL = 0;
    setPWM(dutyCicle);
    OC1CONbits.ON = 1;

    while(1) {
        LATCbits.LATC14 = PORTDbits.RD0;
    }
    
    return 0;
}


void setPWM(unsigned int dutyCicle) {
    if (dutyCicle >= 0 || dutyCicle <= 100)
    {
        OC1RS = (PR3 + 1) * dutyCicle / 100;
    }
}