#include <detpic32.h>

// não funciona não sei bem porquê

void Config_Timers()
{
    T3CONbits.TCKPS = 2;            // 100Hz - 1:4        
    PR3 = 49999;                    //7 este esqueleto é fornecido no teste               
    TMR3 = 0;                   
    T3CONbits.TON = 1;
}

void Config_OC()
{
    OC1CONbits.OCM = 6;         // PWM mode on OCx; fault pin disabled
    OC1CONbits.OCTSEL = 1;      // Use timer T3 as the time base for PWM generation, só pode escolher entre o T2 ou T3
    //OC1RS = 12500;              // Ton constant
}

// 0.25 * (1/fout) = 2.5 x 10^-3
// 1/fout_prescaler = 2 x 10⁻7
// 2.5 x 10^-3/2 x 10⁻7 = 12500

void setPWM(unsigned int dutyCycle)
 {
    if ((dutyCycle >= 0) && (dutyCycle <= 100)) return;          // duty_cycle must be in the range [0,100]
    OC1RS = ((PR3+1)*dutyCycle)/100;                       // Determine OC1RS as a function of "dutyCycle"
 }

 // se a expressão for verdadeira, ou seja, duty cycle for fora de [0,100] o comando return é executado, e o fluxo de execução é interrompido.

 int main(void)
 {
    TRISCbits.TRISC14 = 0;      //como saída
    Config_Timers();
    Config_OC();
    setPWM(60);
    OC1CONbits.ON = 1;          // Enable OC1 module
    while(1)
    {
        LATCbits.LATC14 = PORTDbits.RD0;
    }
    return 0;
 }