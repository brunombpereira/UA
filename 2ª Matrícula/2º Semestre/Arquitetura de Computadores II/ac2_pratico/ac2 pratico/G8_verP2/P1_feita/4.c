#include <detpic32.h>

// o 1 aparece depois de quatro 3's porque vai coincidir nos múltiplos de 5

void Config_Timers()
{
   T1CONbits.TCKPS = 2;            // Timer 1 (5Hz) 1:64               
   PR1 = 62499;                
   TMR1 = 0;                   
   T1CONbits.TON = 1;

// aumentamos freq para o dobro mas a constante de divisão vem para metade dá exatamente a mesma constante
// com a freq. a 50Hz. 50hz = 5hz x 10. logo no terminal vemos 10 3's, uma vez que a sua frequência é 10x maior que a do '1'
   T3CONbits.TCKPS = 3;            // Timer 3 (25Hz)1:16               
   PR3 = 49999;                    // Timer 3 (50Hz)1:8, mesma constante
   TMR3 = 0;                   
   T3CONbits.TON = 1;
}

void Config_Interrupt_Timers()
{
    IPC3bits.T3IP = 2;      // Interrupt priority (must be in range [1..6])
    IEC0bits.T3IE = 1;      // Enable timer T3 interrupts
    IFS0bits.T3IF = 0;      // Reset timer T3 interrupt flag 

    IPC1bits.T1IP = 2;      // Interrupt priority (must be in range [1..6])
    IEC0bits.T1IE = 1;      // Enable timer T3 interrupts
    IFS0bits.T1IF = 0;      // Reset timer T3 interrupt flag 
    EnableInterrupts();
}

int main(void)
 {
    Config_Timers();
    Config_Interrupt_Timers();
    while(1);
    return 0;
 } 

 void _int_(4) isr_T1(void)
 {
       putChar('1');               // print character '1'
       IFS0bits.T1IF = 0;          // Reset T1IF flag
 }
 void _int_(12) isr_T3(void)
{ 
       putChar('3');               // print character '3'
       IFS0bits.T3IF = 0;          // Reset T3IF flag
 }

