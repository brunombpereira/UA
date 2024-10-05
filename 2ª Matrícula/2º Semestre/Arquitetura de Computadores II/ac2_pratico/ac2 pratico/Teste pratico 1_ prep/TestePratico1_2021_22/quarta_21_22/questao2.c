#include <detpic32.h>

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
    AD1CON1bits.ON = 1;         // Enable A/D converter 
                                // This must the last command of the A/D
                                // configuration sequence
}

int main(void)
{
    Config_ADC();
    int i, soma = 0, media = 0;
    TRISDbits.TRISD5 = 0;               //RD5 configurado como saída
    TRISB = TRISB & 0x80FF;             // RB14..8 como saídas, 7 segmentos
    TRISEbits.TRISE1 = 0;               // RE1 como saída
    LATEbits.LATE1 = 0;                 // começar apagado

    while(1)
    {
        AD1CON1bits.ASAM = 1;           // start conversion

        while (IFS1bits.AD1IF == 0 );   // polling
        int *p = (int*)(&ADC1BUF0);
        for( i = 0 ; i < 16 ; i++)
        {
            soma += p[i*4];
        }
        media = soma/2;
        printStr("\nMedia:");           // linhas consecutivas
        printInt(media, 16 | 3 << 16);

        LATDbits.LATD5 = 1;             // RD5 ativo

        if( media <= 102)
        {
            LATB = (LATB & 0x80FF) | 0x3F00;      // 0
        }
        if( (media > 102) && (media <= 204))
        {
            LATB = (LATB & 0x80FF) | 0x0600;      // 1
        }
        if( (media > 204) && (media <= 306))
        {
            LATB = (LATB & 0x80FF) | 0x5B00;      // 2
        }
        if( (media > 306) && (media <= 408))
        {
            LATB = (LATB & 0x80FF) | 0x4F00;      // 3
        }
        if( (media > 408) && (media <= 510))
        {
            LATB = (LATB & 0x80FF) | 0x6600;      // 4
        }
        if( (media > 510) && (media <= 612))
        {
            LATB = (LATB & 0x80FF) | 0x6D00;      // 5
        }
        if( (media > 612) && (media <= 714))
        {
            LATB = (LATB & 0x80FF) | 0x7D00;      // 6
        }
        if( (media > 714) && (media <= 816))
        {
            LATB = (LATB & 0x80FF) | 0x0700;      // 7
        }
        if( (media > 816) && (media <= 918))
        {
            LATB = (LATB & 0x80FF) | 0x7F00;      // 8
        }
        if( media > 918)
        {
            LATB = (LATB & 0x80FF) | 0x6F00;      // 9
        }

        LATEbits.LATE1 = !LATEbits.LATE1;         // toggle do LED RE1

        resetCoreTimer();
        while(readCoreTimer() < 4000000);         // f = 5hz

        IFS1bits.AD1IF = 0;                       // dar reset á interrupt flag
        soma = 0;
        media = 0;
    }

}
