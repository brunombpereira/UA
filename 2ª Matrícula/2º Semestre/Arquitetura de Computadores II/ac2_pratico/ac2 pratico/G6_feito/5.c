#include <detpic32.h>
//Verificam-se mais valores, visto que se se 
//realizam 4 amostras por interrupção


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
    int i = 0;
    int soma = 0, media = 0, tensao = 0;

    while(1)
    {
        AD1CON1bits.ASAM = 1;                       // Start conversion
        while(IFS1bits.AD1IF == 0);                 // quando a conversao acaba IFS1bits.AD1IF == 0 e colocado a 1 automaticamente, dai ser necessario 
                                                    // colocar a 0 manualmente no final do ciclo. se nao fica eternamente em estado de interrupcao

       int *p = (int *)(&ADC1BUF0); 
       for(i = 0; i < 16; i++ ) { 
        soma += p[i*4];
        media =  soma/4;   
        printStr("\nMedia:");                          // média das 4 amostras por conversão
        printInt(media, 10 | 4 << 16);                 // 0x0004000A
        tensao = (media*33+511)/1023;
        printStr("\nAmplitude em Tensão:");
        printInt(tensao, 10 | 2 << 16);
        
        IFS1bits.AD1ID = 0;
        sum = 0;                                       // vou ter uma soma nova a cada conversão de 4 amostras
       }
       IFS1bits.AD1IF == 0;                            // depois da leitura sempre!!
    }
}