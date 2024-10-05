#include <detpic32.h>


void delay(unsigned int ms);
void send2displays(unsigned char value);
unsigned char toBcd(unsigned char value);


volatile unsigned char voltage = 0;         // Global variable


int mais(void) {
    unsigned int cnt = 0;

    // Configuration of digital I/O:

    TRISB = TRISB & 0x80FF;                 // Configure RB8-RB14 as outputs
    TRISD = TRISD & 0xFF9F;                 // Configure RD5-RD6 as outputs
    LATB = LATB & 0x80FF;                   // Colocar a 0, começam apagados

    // Configuration of analog input & A/D module:

    TRISBbits.TRISBx = 1;                   // RBx digital output disconnected
    AD1PCFGbits.PCFGx = 0;                  // RBx configured as analog input
    AD1CON1bits.SSRC = 7;                   // Conversion trigger selection bits: in this mode an internal counter ends sampling and starts conversion
    AD1CON1bits.CLRASAM = 1;                // Stop conversions when the first A/D converter interrupt is generated. At the same time, hardware clears the ASAM bit
    AD1CON3bits.SAMC = 16;                  // Sample time is 16 TAD (TAD = 100ns)
    AD1CON2bits.SMPI = 7;                   // Interrupt is generated after N samples (replace N by the desired number of consecutive samples) (N - 1)
    AD1CHSbits.CH0SA = x;                   // Replace x by the desired input analog channel (0 to 15)
    AD1CON1bits.ON = 1;                     // Enable A/D converter

    // Configure interrupt system:

    IPC6bits.AD1IP = 2;                     // Configure priority of A/D interrupts
    IFS1bits.AD1IF = 0;                     // Clear A/D interrupt flag
    IEC1bits.AD1IE = 1;                     // Enable A/D interrupts
    EnableInterrupts();                     // Global interrupt enable

    while (1)
    {
        if (cnt == 0)                       // 0, 200ms, 400ms, ... (5 samples/second)
        {
            AD1CON1bits.ASAM = 1;           // Start A/D conversion
        }

        send2displays(voltage);

        cnt = (cnt + 1) % 20;               // Frequência de amostragem de 5 Hz
        delay(10);                          // Frequência de refrescamento de 100 Hz
    }
    return 0;                               // All activity is done by the ISR
}


// Interrupt Handler

void _int_(VECTOR) isr_adc(void) {          // Replace VECTOR by the A/D vector number - see "PIC32 family data sheet" (pages 74-76)
    int soma, tensao, avarage = 0;
    int i;
    int *p = (int *)(&ADC1BUF0);

    for (int i = 0; i < 8; i++)             
    {
        soma += p[i * 4];                   // Leitura do valor das amostras
    }

    avarage = soma / 8;                     
    tensao = (avarage * 33 + 511) / 1023;
    voltage = toBcd(tensao);                // Converter para decimal
    
    IFS1bits.AD1IF = 0;                     // Reset AD1IF flag
}


void delay(unsigned int ms) {
    int k = 20000 * ms;
    resetCoreTimer();
    while(readCoreTimer() < k);
}


void send2displays(unsigned char value) {
    static const char display7seg[] = {0x3F, 0x06,0x5b,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
    static char displayFlag = 0;

    int dl, low, dh, high;

    // O shift é para colocar o valor entre 0 e 15, se não fosse feito >> 4, o programa ia ao array display7seg buscar um valor entre 16 e 256
    
    dl = value & 0x0F;                      // Send digit_low (dl) to display: dl = value & 0x0F, com os bits menos significativos
    dh = (value & 0x00F0) >> 4              // Send digit_high (dh) to display: dh = (value & 0x00F0) >> 4, com os bits mais significativos

    if (displayFlag == 0)
    {
        LATDbits.LATD5 = 1;                 // Select display low
        LATDbits.LATD6 = 0;

        low = display7seg[dl];

        LATB = (LATB & 0x80FF) | (low << 8);
    } else
    {
        LATDbits.LATD5 = 0;                 // Select display high
        LATDbits.LATD6 = 1;

        high = display7seg[dh]

        LATB = (LATB & 0x80FF) | (high << 8);
    }

    displayFlag = !displayFlag;
}


unsigned char toBcd(unsigned char value) {
    return ((value / 10) << 4) + (value % 10);
}