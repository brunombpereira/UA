#include <detpic32.h>

// Se se pretender que o timer gere interrupções é necessário, para além da configuração-base 
// apresentada no ponto anterior, configurar o sistema de interrupções na parte respeitante ao timer

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
    putChar('.');
    IFS0bits.T3IF = 0;          // Reset T3 interrupt flag
 }