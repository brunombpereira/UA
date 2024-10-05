#include <detpic32.h>

// medi 1.58 u seg

void Config_ADC()
{
    TRISBbits.TRISB4 = 1;       // RBx digital output disconnected
    AD1PCFGbits.PCFG4= 0;       // RBx configured as analog input
    AD1CON1bits.SSRC = 7;       // Conversion trigger selection bits: in this
                                // mode an internal counter ends sampling and
                                // starts conversion
    AD1CON1bits.CLRASAM = 1;    // Stop conversions when the 1st A/D converter
                                // interrupt is generated. At the same time,
                                // hardware clears the ASAM bit
    AD1CON3bits.SAMC = 16;      // Sample time is 16 TAD (TAD = 100 ns)
    AD1CON2bits.SMPI = 2-1;     // Interrupt is generated after N samples
                                // (replace N by the desired number of
                                // consecutive samples)
    AD1CHSbits.CH0SA = 4;       // replace x by the desired input
                                // analog channel (0 to 15)
    AD1CON1bits.ON = 1;         // Enable A/D converter (se nao for feito, o ADC nao funciona)
                                // This must the last command of the A/D
                                // configuration sequence 
}

void Config_Interrupt()
{
    IPC6bits.AD1IP = 2;         // configure priority of A/D interrupts
    IFS1bits.AD1IF = 0;         // clear A/D interrupt flag
    IEC1bits.AD1IE = 1;         // enable A/D interrupts
    EnableInterrupts();         // Macro defined in "detpic32.h"
}

int main(void)
 {
    TRISDbits.TRISD11 = 0;      // RD11 configurado como saída
    Config_ADC();
    Config_Interrupt();         // Configure all (digital I/O, analog input, A/D module)
    EnableInterrupts();         // Global Interrupt Enable
    AD1CON1bits.ASAM = 1;       // Start A/D conversion
    while(1)                    // all activity is done by the ISR
    {                   
    LATDbits.LATD11 = 0;
    }
    return 0;
 } 

 // Interrupt Handler, funcoes void indica que nao retornam nada
 void _int_(27) isr_adc(void)                  // Replace VECTOR by the A/D vector
 {
    volatile int adc_value;
    adc_value = ADC1BUF0;
    AD1CON1bits.ASAM = 1;                      // Start A/D conversion
    IFS1bits.AD1IF = 0;                        // Reset AD1IF flag
    LATDbits.LATD11 = 1;
 }