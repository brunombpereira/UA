#include <detpic32.h>

void Config_Timers()
{
   T1CONbits.TCKPS = 2;            // Timer 1 (5Hz) 1:64               
   PR1 = 62499;                
   TMR1 = 0;                   
   T1CONbits.TON = 1;

   T3CONbits.TCKPS = 4;            // Timer 3 (25Hz)1:16               
   PR3 = 49999;                    
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

void Config_IO()
{
    TRISDbits.TRISD0 = 0;           // RD0 e RD2 como saídas
    TRISDbits.TRISD2 = 0;
    LATDbits.LATD0 = 0;             // inicializá-los a 0
    LATDbits.LATD2 = 0;
    TRISEbits.TRISE1 = 0;           // RE1 e RE3 como saídas
    TRISEbits.TRISE3 = 0;
    LATEbits.LATE1 = 0;             // inicializá-los a 0
    LATEbits.LATE3 = 0;
}

int main(void)
 {
       Config_IO();
       Config_Timers();
       Config_Interrupt_Timers();
       while(1);
       return 0;
 } 

 void _int_(4) isr_T1(void)
 {
       LATDbits.LATD0 = !LATDbits.LATD0;   // toggle do RD0
       LATEbits.LATE1 = !LATEbits.LATE1;   // toggle do RE1
       IFS0bits.T1IF = 0;                  // Reset T1IF flag
 }
 void _int_(12) isr_T3(void)
{ 
       LATDbits.LATD2 = !LATDbits.LATD2;   // toggle do RD2
       LATEbits.LATE3 = !LATEbits.LATE3;   // toggle do RE3
       IFS0bits.T3IF = 0;                  // Reset T3IF flag
 }