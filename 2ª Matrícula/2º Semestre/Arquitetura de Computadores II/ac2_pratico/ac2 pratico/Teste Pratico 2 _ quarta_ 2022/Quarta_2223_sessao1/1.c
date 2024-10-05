#include <detpic32.h>

void Config_Timer()
{
    T3CONbits.TCKPS = 2;            // 1:4 prescaler - Fout = 120Hz
    PR3 = 41666;                    // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz 
    TMR3 = 0;                       // Reset timer T2 count register 
    T3CONbits.TON = 1;              // Enable timer T2 (must be the last command of the timer configuration sequence) 
}

int main(void)
{
    TRISBbits.TRISB0 = 1;           // RB2  e RB0 como entradas
    TRISBbits.TRISB2 = 1;

    Config_Timer();

    OC2CONbits.OCM = 6;             // PWM mode on OCx; fault pin disabled 
    OC2CONbits.OCTSEL = 1;          // 0 se for usado timer T2 as the time base for PWM generation ou 1 se for usado o T3
    OC2RS = 31200;                  // duty cycle de 75% por default
    OC2CONbits.ON = 1;              // Enable OC1 module 

    while(1)
    {
        if((PORTBbits.RB2 == 0) && (PORTBbits.RB0 == 0))
        {
            OC2RS = 12500;                  // duty cycle de 30% por default
        }
        if((PORTBbits.RB2 == 1) && (PORTBbits.RB0 == 1))
        {
            OC2RS = 22917;                  // duty cycle de 55% por default
        }
        resetCoreTimer();
        while(readCoreTimer() < 7200);      // esperar 360useg = 0.360 mseg -> 2.777 Hz
    }
    return 0;
}