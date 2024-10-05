#include <detpic32.h>

volatile int voltage = 0; // Global variable

void Config_Timers()
{
    // Configure Timer T3 with interrupts enabled (100Hz)
    T3CONbits.TCKPS = 2;            // 1:4        
    PR3 = 49999;                
    TMR3 = 0;                   
    T3CONbits.TON = 1; 

    // Configure Timer T1 with interrupts enabled (5Hz)
    T1CONbits.TCKPS = 6;            // 1:64  
    PR1 = 62499;                
    TMR1 = 0;                   
    T1CONbits.TON = 1; 
}

void Config_Interrupts()
{
    IPC3bits.T3IP = 2;      // Interrupt priority (must be in range [1..6])
    IEC0bits.T3IE = 1;      // Enable timer T3 interrupts
    IFS0bits.T3IF = 0;      // Reset timer T3 interrupt flag 

    IPC1bits.T1IP = 2;      // Interrupt priority (must be in range [1..6])
    IEC0bits.T1IE = 1;      // Enable timer T1 interrupts
    IFS0bits.T1IF = 0;      // Reset timer T1 interrupt flag 

    IPC6bits.AD1IP = 2;     // Global interrupt systes for ADC1
    IEC1bits.AD1IE = 1;
    IFS1bits.AD1IF = 0;

    EnableInterrupts();      // Global Interrupt Enable
}

void Config_IO()
{
    TRISB = TRISB & 0x80FF;
    LATB = LATB & 0x80FF;
    TRISD = TRISD & 0xFF9F;
    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 1;
}

void Config_ADC()
{
    TRISBbits.TRISB4 = 1; 
    AD1PCFGbits.PCFG4= 0; 
    AD1CON1bits.SSRC = 7; 
    AD1CON1bits.CLRASAM = 1;
    AD1CON3bits.SAMC = 16; 
    AD1CON2bits.SMPI = 4-1;         // nr de amostras em cada conversão
    AD1CHSbits.CH0SA = 4; 
    AD1CON1bits.ON = 1; 
}

void send2displays(unsigned char value)
 {
    static const char display7Scodes[] = {0x3F, 0x06,0x5b,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
    static char displayFlag = 0;          // static variable: doesn't loose its value between calls to function
    
    int dh,dl,low,high;
    // o shift e para colocar o valor entre 0 e 15, se nao fizesse >> 4, o programa ia ao array display7Scodes buscar um valor entre 16-256
    dh = (value & 0x00F0) >> 4;           // send digit_high (dh) to display: dh = value >> 4, com os bits mais significativos
    dl = value & 0x0F;                    // send digit_low (dl) to display: dl = value & 0x0F, com os bits menos significativos
    
    if (displayFlag == 0)
        {
        LATDbits.LATD6 = 0;                   // select display low
        LATDbits.LATD5 = 1; 
        low = display7Scodes[dl];
        LATB = (LATB & 0x80FF) | (low << 8);
        }
    else
    {
        LATDbits.LATD6 = 1;                   // select display high
        LATDbits.LATD5 = 0;      
        high = display7Scodes[dh];
        LATB = (LATB & 0x80FF) | (high << 8); // o high esta nos bits 7-4, fazemos shift de 8 para os colocar nos 15-12
    }
    displayFlag = !displayFlag;
}

unsigned char toBcd(unsigned char value)
 {
    return ((value / 10) << 4) + (value % 10);
 }

int main(void)
{
    Config_Timers();         // Function to configure all (digital I/O, analog input, A/D module)
    Config_Interrupts();
    Config_IO();
    Config_ADC();
    while(1);
    return 0;
} 

void _int_(4) isr_T1(void)
 {
    AD1CON1bits.ASAM = 1;       // Start A/D conversion
    IFS0bits.T1IF = 0;          // Reset T1IF flag
 }

 void _int_(12) isr_T3(void)
 {
    send2displays(toBcd(voltage));         // Send the value of the global variable "voltage" to the displays, using BCD (decimal) format
    IFS0bits.T3IF = 0;                     // Reset T3IF flag
 }

 void _int_(27) isr_adc(void)
{
    int soma = 0,media = 0, i;

    int *p = (int *)(&ADC1BUF0);                // Calculate buffer average (8 samples)

    for( i=0;i<4;i++)
    {
        soma += p[i*4];
    }

    media = soma/4;
    voltage =(media*33+511)/1023;                    // Calculate voltage amplitude and copy it to "voltage"
    IFS1bits.AD1IF = 0;                         // Reset AD1IF flag
    soma = 0;
}
