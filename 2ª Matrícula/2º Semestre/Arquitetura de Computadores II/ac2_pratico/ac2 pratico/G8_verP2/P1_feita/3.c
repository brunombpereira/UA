#include <detpic32.h>

volatile int count = 0;

void Config_Timers()
{
   T3CONbits.TCKPS = 7;               // raciocínio do último código
   PR3 = 39062;                
   TMR3 = 0;                   
   T3CONbits.TON = 1;
}

void Config_Interrupt_Timers()
{
   IPC3bits.T3IP = 2;
   IEC0bits.T3IE = 1;
   IFS0bits.T3IF = 0;
   EnableInterrupts();
}

int main(void)
 {
   Config_Timers();
   Config_Interrupt_Timers();
   while(1);
   return 0;
 } 

void _int_(12) isr_T3(void)     // Replace VECTOR by the timer T vector number
{
    count ++;                   // chamar o system call putChar a cada 2 interrupções
    if (count % 2 == 0)          // imprime a cada 2 contagens, logo a 1Hz
    {
    putChar('.');               // evocado 2 vezes a cada 2hz logo 1hz
    }
    IFS0bits.T3IF = 0;          // Reset T3 interrupt flag
 }
