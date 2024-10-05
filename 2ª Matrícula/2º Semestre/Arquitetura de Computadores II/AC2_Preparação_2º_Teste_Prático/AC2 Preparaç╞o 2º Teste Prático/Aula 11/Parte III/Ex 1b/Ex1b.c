#include <detpic32.h>


volatile int voltage = 0;             // Global variable
volatile int voltMin = 0;
volatile int voltMax = 0;


void send2displays(unsigned char value);
unsigned char toBcd(unsigned char value);


int main (void)
{
    // Configuration of digital I/O:

    TRISB = TRISB & 0x80FF;                     // Configure RB8-RB14 as outputs
    TRISD = TRISD & 0xFF9F;                     // Configure RD5-RD6 as outputs                             
    LATB = LATB & 0x80FF;                       // Colocar a 0, começam apagados
    LATDbits.LATD5 = 1;
    LATDbits.LATD6 = 1;

    // Configuration of analog input & A/D module:

    TRISBbits.TRISB4 = 1;                       // RBx digital output disconnected
    AD1PCFGbits.PCFG4= 0;                       // RBx configured as analog input
    AD1CON1bits.SSRC = 7;                       // Conversion trigger selection bits: in this mode an internal counter ends sampling and starts conversion
    AD1CON1bits.CLRASAM = 1;                    // Stop conversions when the first A/D converter interrupt is generated. At the same time, hardware clears the ASAM bit
    AD1CON3bits.SAMC = 16;                      // Sample time is 16 TAD (TAD = 100ns)
    AD1CON2bits.SMPI = 8-1;                     // Interrupt is generated after N samples (replace N by the desired number of consecutive samples) (N - 1)
    AD1CHSbits.CH0SA = 4;                       // Replace x by the desired input analog channel (0 to 15)
    AD1CON1bits.ON = 1;                         // Enable A/D converter

    // Configure timers T1 & T3:

    T1CONbits.TCKPS = 2;
    PR1 = 62499;
    TMR1 = 0;

    T3CONbits.TCKPS = 2;
    PR3 = 49999;
    TMR3 = 0;

    T1CONbits.TON = 1;
    T3CONbits.TON = 1;

    IPC1bits.T1IP = 2;
    IEC0bits.T1IE = 1;

    IPC3bits.T3IP = 2;
    IEC0bits.T3IE = 1;

    IPC6bits.AD1IP = 2;     // Global interrupt systes for ADC1
    IEC1bits.AD1IE = 1;

    IFS1bits.AD1IF = 0;                         
    IFS0bits.T1IF = 0;                          
    IFS0bits.T3IF = 0; 

    // Configure UART2:

    U2BRG = (20000000 + 8 * 115200) / (16 * 115200) - 1;
    U2MODEbits.BRGH = 0;
    U2MODEbits.PDSEL = 0;
    U2MODEbits.STSEL = 0;
    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;
    U2MODEbits.ON = 1;

    IEC1bits.U2RXIE = 1;
    IEC1bits.U2TXIE = 0;
    IPC8bits.U2IP = 1;
    U2STAbits.UTXISEL = 0;

    EnableInterrupts();

    while(1);
    return 0;
}


void _int_(4) isr_T1(void) {
    AD1CON1bits.ASAM = 1;
    IFS0bits.T1IF = 0;
}


void _int_(12) isr_T3(void) {
    send2displays(toBcd(voltage));

    IFS0bits.T3IF = 0;
}


void _int_(27) isr_ADC(void) {
    int i, soma = 0, media = 0, tensao = 0;
    int *p = (int *)(&ADC1BUF0);

    for (i = 0; i < 4; i++)
    {
        soma += p[i*4];
    }

    media = soma / 4;
    voltage = (media * 33 + 511) / 1023;

    if (voltage > voltMax)
    {
        voltMax = tensao;
    } else if (voltage < voltMin)
    {
        voltMin = tensao;
    }

    IFS1bits.AD1IF = 0;    
    soma = 0;
}


void _int_(32) isr_uart2(void) {
    char c = U2RXREG;

    if (c == 'M')
    {
        putstr("VMax = ");
        putc(0x00);
    } else if (c == 'm')
    {
        putc('r');
    }
    
    
}


void send2displays(unsigned char value) {
    static const char display7seg[] = {0x3F, 0x06,0x5b,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
    static char displayFlag = 0;

    int dl, low, dh, high;

    // O shift é para colocar o valor entre 0 e 15, se não fosse feito >> 4, o programa ia ao array display7seg buscar um valor entre 16 e 256
    
    dl = value & 0x0F;                      // Send digit_low (dl) to display: dl = value & 0x0F, com os bits menos significativos
    dh = (value & 0x00F0) >> 4;             // Send digit_high (dh) to display: dh = (value & 0x00F0) >> 4, com os bits mais significativos

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

        high = display7seg[dh];

        LATB = (LATB & 0x80FF) | (high << 8);
    }

    displayFlag = !displayFlag;
}


unsigned char toBcd(unsigned char value) {
    return ((value / 10) << 4) + (value % 10);
}