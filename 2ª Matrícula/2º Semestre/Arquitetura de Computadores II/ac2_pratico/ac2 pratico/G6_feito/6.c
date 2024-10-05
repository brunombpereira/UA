#include <detpic32.h>
//Verificam-se mais valores, visto que se se 
//realizam 4 amostras por interrupção

void send2displays(unsigned char value)
unsigned char toBcd(unsigned char value)

void Config_IO()
{
    TRISB = TRISB & 0x80FF;                 // initialize ports
    LATB = LATB & 0x80FF;
    TRISD = (TRISD & 0xFF9F) | 0x0060;
}

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
    AD1CON2bits.SMPI = 4-1;     // Interrupt is generated after N samples
                                // (replace N by the desired number of
                                // consecutive samples)
    AD1CHSbits.CH0SA = 4;       // replace x by the desired input
                                // analog channel (0 to 15)
    AD1CON1bits.ON = 1;         // Enable A/D converter (se nao for feito, o ADC nao funciona)
                                // This must the last command of the A/D
                                // configuration sequence 
}

int main (void)
{
    
    Config_ADC();
    Config_IO();                // RB8..14 como saídas e inicializados a 0
                                // RD5 e RD6 como saídas - displays
    int i = 0;
    int soma = 0, media = 0, tensao = 0,tensao_bcd = 0;

    while(1)
    {
        if (i == 0){                     // 0, 200ms, 400ms,600ms..
            AD1CON1bits.ASAM = 1;       // Convert analog input (4 samples)
            while(IFS1bits.AD1IF == 0);
            int *p = (int *)(&ADC1BUF0); 
        for(i = 0; i < 16; i++ ){ 
            soma += p[i*4];
            }
            media =  soma/4;   
            tensao = (media*33+511)/1023;
            tensao_bcd = toBcd(tensao);
            sum = 0;
            media = 0;
            IFS1bits.AD1IF = 0;
        }
        send2displays(tensao_bcd);
        resetCoreTimer();
        while (readCoreTimer() < 200000);       // 10 ms -> 100Hz
        i = (i+1) % 20 ;                        // o resto só dá zero para o valor 10, esta condição vai ser testada 20x demorando 10ms cada
        // vamos ter que cada conversão de 4 amostras vai demorar 200 ms cada, e por tanto vão ocorrer 5 por seg (5hz)
       }
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