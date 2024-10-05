#include <detpic32.h>

void Config_Timer()
{
    T2CONbits.TCKPS = 2;        // 1:4 prescaler (i.e Fout_presc = 5 Mhz) 
    PR2 = 33333;                // f_out = 150Hz
    TMR2 = 0;                   // Reset timer T2 count register 
    T2CONbits.TON = 1;          // Enable timer T2 (must be the last command of the timer configuration sequence)  
}

int main (void)
{
    TRISBbits.TRISB3 = 1;       // RB3 como entrada
    TRISBbits.TRISB0 = 1;       // RB0 como entrada

    Config_Timer();
    
    OC2CONbits.OCM = 6;         // PWM mode on OCx; fault pin disabled 
    OC2CONbits.OCTSEL = 0;      // Use timer T2 as the time base for PWM generation 
    OC2RS = 8333;               // Ton constant 
    OC2CONbits.ON = 1;          // Enable OC1 module

    while (1)
    {
        if((PORTBbits.RB3 == 0) && (PORTBbits.RB0 == 1))        // duty = 25%
        {
            OC2RS = 8334;                                       // Ton constant 
        }
        if((PORTBbits.RB3 == 1) && (PORTBbits.RB0 == 0))        // duty = 70%
        { 
            OC2RS = 23333;                                      // Ton constant 
        }

        resetCoreTimer();                                       // verificar a cada 250useg os valores presentes no switches
        while(readCoreTimer() < 5000)                           // 250useg = 0.250 ms - 4Hz
    }
}