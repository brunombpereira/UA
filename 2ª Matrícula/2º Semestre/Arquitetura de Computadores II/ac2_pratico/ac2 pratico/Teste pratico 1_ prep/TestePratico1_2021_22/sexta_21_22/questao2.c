#include <detpic32.h>
// complemento para um: negar todos os bits
void Config_ADC()
{
    TRISBbits.TRISB4 = 1;           // RBx digital output disconnected 
    AD1PCFGbits.PCFG4= 0;           // RBx configured as analog input 
    AD1CON1bits.SSRC = 7;           // Conversion trigger selection bits: in this 
                                    // mode an internal counter ends sampling and 
                                    // starts conversion 
    AD1CON1bits.CLRASAM = 1;        // Stop conversions when the 1st A/D converter 
                                    // interrupt is generated. At the same time, 
                                    // hardware clears the ASAM bit 
    AD1CON3bits.SAMC = 16;          // Sample time is 16 TAD (TAD = 100 ns) 
    AD1CON2bits.SMPI = 4-1;         // Interrupt is generated after N samples 
                                    // (replace N by the desired number of 
                                    // consecutive samples) 
    AD1CHSbits.CH0SA = 4;           // replace x by the desired input 
                                    // analog channel (0 to 15) 
    AD1CON1bits.ON = 1;             // Enable A/D converter 
                                    // This must the last command of the A/D
                                    // configuration sequence
}

int main(void)
{
    Config_ADC();
    int i, com = 0,soma = 0, media = 0; // usar outro variável para a media em complemente, pois vamos precisar da media para definir gamas
    TRISBbits.TRISB3 = 1;               // RB3 configurado como entrada
    TRISB = TRISB & 0x80FF;             // displays 7 segmentos configurados como saída
    TRISD = TRISD & 0xFF9F;             // RD5 e RD6 configurados como saídas
    TRISEbits.TRISE1 = 0;               // RE6 e RE1 configurados como saídas
    TRISEbits.TRISE6 = 0;
    LATEbits.LATE1 = 0;                 // valor inicial dos leds: RE6 = 1, RE0 = 0;
    LATEbits.LATE6 = 1;

    while(1)
    {
        AD1CON1bits.ASAM = 1;                   // começar a conversão

        while(IFS1bits.AD1IF == 0);             // enquanto não houver interrupção ficamos aqui num ciclo de polling á espera

        int *p = (int*)(&ADC1BUF0);
            for (i= 0; i<16;i++)
            {
                soma += p[i*4];
            }
            media = soma / 4;
        com = (~media) & 0x00000FFF;            // negar todos os bits da media e manter 12 bits, negando 1023 ficará 11 0000000000 
                                                // o ADC interno está programado para 10 bits e nós estamos a apresentar o resultado com 12.
        printStr("Media:");
        printInt(com, 2 | 12 << 16);
        putChar(' ');

        if (PORTBbits.RB3 == 1)
        {
            LATDbits.LATD5 = 1;
            LATDbits.LATD6 = 0;
        }
        if (PORTBbits.RB3 == 0)
        {
            LATDbits.LATD5 = 0;
            LATDbits.LATD6 = 1;
        }
        // 4 a E são 11 gamas : 1023 / 11 = 93 
        if ( media <= 93)
        {
            LATB = (LATB & 0x80FF) | 0x6600;    // 4
        }
        if ( (media > 93) && (media <=186) )
        {
            LATB = (LATB & 0x80FF) | 0x6D00;    // 5
        }
        if ( (media > 186) && (media <= 279) )
        {
            LATB = (LATB & 0x80FF) | 0x7D00;    // 6
        }
        if ( (media > 279) && (media <= 372) )
        {
            LATB = (LATB & 0x80FF) | 0x0700;    // 7
        }
        if ( (media > 372) && (media <= 465) )
        {
            LATB = (LATB & 0x80FF) | 0x7F00;    // 8
        }
        if ( (media > 465) && (media <= 558) )
        {
            LATB = (LATB & 0x80FF) | 0x6F00;    // 9
        }
        if ( (media > 558) && (media <= 651) )
        {
            LATB = (LATB & 0x80FF) | 0x7700;    // A
        }
        if ( (media > 651) && (media <= 744) )
        {
            LATB = (LATB & 0x80FF) | 0x7C00;    // B
        }
        if ( (media > 744) && (media <= 837) )
        {
            LATB = (LATB & 0x80FF) | 0x3900;    // C
        }
        if ( (media > 837) && (media <= 930) )
        {
            LATB = (LATB & 0x80FF) | 0x5E00;    // D
        }
        if ( media > 930 )
        {
            LATB = (LATB & 0x80FF) | 0x7900;    // E
        }

        PORTEbits.RE1 = !PORTEbits.RE1;         // toggle dos leds ligados a RE6 e RE1
        PORTEbits.RE6 = !PORTEbits.RE6;

        IFS1bits.AD1IF = 0;

        resetCoreTimer();
        while(readCoreTimer() < 5000000);       // conversões feitas a 4hz

        soma = 0;
        media = 0;
    }
}
