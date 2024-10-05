#include <detpic32.h>
void _int_(8) isr_T2(void);
void _int_(7) isr_INT1(void);

// não dá para temporizar 0.3333 seg (?)

void Config_Timers()
{
   // configuração do Timer para 2Hz
   T2CONbits.TCKPS = 7;            // Timer 2              
   PR2 = 39062;                    
   TMR2 = 0;                   
   T2CONbits.TON = 1;
}

void Config_Interrupts()
{
    IPC2bits.T2IP = 2;      // Interrupt priority (must be in range [1..6])
    IEC0bits.T2IE = 0;      // Enable timer T2 interrupts
    IFS0bits.T2IF = 0;      // Reset timer T2 interrupt flag 

    INTCONbits.INT1EP = 0;          // External Interrupt 1 Edge Polarity Control bit - descendent

    IPC1bits.INT1IP = 2;      // Interrupt priority (must be in range [1..6])
    IEC0bits.INT1IE = 1;      // Enable timer T2 interrupts
    IFS0bits.INT1IF = 0;      // Reset timer T2 interrupt flag 

    EnableInterrupts();
}

void Config_IO()
{
    TRISDbits.TRISD8 = 1;           // RD8/Int1 configurado como entrada
    TRISEbits.TRISE0 = 0;           // RE0 como saída
    LATEbits.LATE0 = 0;
}

int main (void)
{
    Config_IO();
    Config_Timers();
    Config_Interrupts();
    while(1);
    return 0;
}

void _int_(8) isr_T2(void)          // implementar um contador de módulo 5
{
    static int count = 0;
    if (++count == 6)
    {
        LATEbits.LATE0 = 0;         // desliga o LED ao fim de 3 segundos
        count = 0;                  // reset ao counter
        IEC0bits.T2IE = 0;          // desativar a sua própria interrupção
    }
    
    IFS0bits.T2IF = 0;              // Reset timer T2 interrupt flag
}

void _int_(7) isr_INT1(void)        // funciona com transições de relógio
{
    LATEbits.LATE0 = 1;             // ligar o LED, ao fim de 0.6 ativa interrupções, vai para a rsi do T2, verificar com o contador, enquanto != 0 permanece ligado

    IEC0bits.T2IE = 1;              // ativar T2 interrupções
    TMR2 = 0;                       // Reset ao Timer

    IFS0bits.INT1IF = 0;
}

