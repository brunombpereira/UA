#include <detpic32.h>

void Config_ADC()
{
    TRISBbits.TRISB4 = 1;               // RBx digital output disconnected 
    AD1PCFGbits.PCFG4= 0;               // RBx configured as analog input 
    AD1CON1bits.SSRC = 7;               // Conversion trigger selection bits: in this 
                                        // mode an internal counter ends sampling and 
                                        // starts conversion 
    AD1CON1bits.CLRASAM = 1;            // Stop conversions when the 1st A/D converter 
                                        // interrupt is generated. At the same time, 
                                        // hardware clears the ASAM bit 
    AD1CON3bits.SAMC = 16;              // Sample time is 16 TAD (TAD = 100 ns) 
    AD1CON2bits.SMPI = 2-1;             // Interrupt is generated after N samples 
                                        // (replace N by the desired number of 
                                        // consecutive samples) 
    AD1CHSbits.CH0SA = 4;               // replace x by the desired input 
                                        // analog channel (0 to 15) 
    AD1CON1bits.ON = 1;                 // Enable A/D converter 
                                        // This must the last command of the A/D
                                        // configuration sequence 
}

int main(void)
{
    Config_ADC();
    int i,soma=0,media=0;
    TRISB = TRISB & 0x80FF;                        // displays de 7 segmentos como saídas
    LATB = LATB & 0x80FF;                          // para eles começarem apagados
    TRISD = TRISD & 0xFF9F;                        // RD6 e RD5 como saídas
    LATD = LATD & 0xFF9F;                          // começarem os 2 apagados
    TRISEbits.TRISE1 = 0;                          // RE1 como saída
    LATEbits.LATE1 = 0;                            // começa apagado, com o valor 0

    while(1)
    {
        AD1CON1bits.ASAM = 1;                       // Start conversion
        while(IFS1bits.AD1IF == 0);                 // quando a conversao acaba IFS1bits.AD1IF == 0 e colocado a 1 automaticamente, dai ser necessario 
                                                    // colocar a 0 manualmente no final do ciclo. se nao fica eternamente em estado de interrupcao

       int *p = (int *)(&ADC1BUF0); 
        for( i = 0; i < 16; i++ ) { 
            soma += p[i*4];
        }
       media = soma/2; 
       printStr("\nMedia:"); 
       printInt(media, 16 | 3 << 16 );             // hexadecimal, com 3 dígitos
       putChar('\n');                              // para os resultados aparecerem em linhas consecutivas do terminal

    // atribuir gamas de valores da média a um nr entre 0 e 9 e mostrar no display menos significativo
        LATDbits.LATD5 = 1;                        // ligar display menos significativo 

        if(media <= 102)                            // dividimos o valor máximo que a média pode ter por 10, que são as gamas em que queremos dividir.
            LATB = (LATB & 0x80FF) | 0x3F00;        // 0 nos segmentos
        if((media >102) && (media <= 204))
            LATB = (LATB & 0x80FF) | 0x0600;        // 1 nos segmentos 
        if((media >204) && (media <= 306))
            LATB = (LATB & 0x80FF) | 0x5B00;        // 2 nos segmentos x 1 0 1   1 0 1 1
        if((media >306) && (media <= 408))
            LATB = (LATB & 0x80FF) | 0x4F00;        // 3 nos segmentos x 1 0 0   1 1 1 1
        if((media >408) && (media <= 510))
            LATB = (LATB & 0x80FF) | 0x6600;        // 4 nos segmentos x 1 1 0   0 1 1 0
        if((media >510) && (media <= 612))
            LATB = (LATB & 0x80FF) | 0x6D00;        // 5 nos segmentos x 1 0 1   1 1 0 1 - VERIFICAR CODIGO HEXA.
        if((media >612) && (media <= 714))
            LATB = (LATB & 0x80FF) | 0x7D00;        // 6 nos segmentos
        if((media >714) && (media <= 816))
            LATB = (LATB & 0x80FF) | 0x0700;        // 7 nos segmentos
        if((media >816) && (media <= 918))
            LATB = (LATB & 0x80FF) | 0x7F00;        // 8 nos segmentos
        if((media > 918))
            LATB = (LATB & 0x80FF) | 0x6F00;        // 9 nos segmentos


        LATEbits.LATE1 = !LATEbits.LATE1;
        soma = 0;                                   // dar reset ao valor da soma, para que na nova conversão seja armazenado o novo valor.
        media = 0;
        IFS1bits.AD1IF = 0;                         // depois da leitura sempre!!

        resetCoreTimer();                           // f = 5hz, 20ms entre cada conversão, assim temos 5 convesões por seg.
        while(readCoreTimer() < 4000000 );
    }
}
