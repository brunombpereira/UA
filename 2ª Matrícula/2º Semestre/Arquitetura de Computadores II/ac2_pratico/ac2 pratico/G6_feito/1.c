// LSB = Vmax/2^N - 1 = no nosso caso = 3.3/1024-1 = 3.2mV que e a tensao minima necessaria para que haja mudanca de nivel 

// AD1CHS e um valor com 4 bits que vai selecionar 1 das 16 entradas do multiplexor
// todas as entradas do porto B sao digitais por defeito, temos de as configurar como analógica
// ADC1BUF 0...15 sao preenchidos conforme o nr de conversoes que facamos
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
    AD1CON2bits.SMPI = 1-1;     // Interrupt is generated after N samples
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

    while(1)
    {
        AD1CON1bits.ASAM = 1;                       // Start conversion
        while(IFS1bits.AD1IF == 0);                 // quando a conversao acaba IFS1bits.AD1IF == 0 e colocado a 1 automaticamente, dai ser necessario 
                                                    // colocar a 0 manualmente no final do ciclo. se nao fica eternamente em estado de interrupcao

        printInt(ADC1BUF0, 10 | 3 << 16);           // imprimir o valor guardado no primeiro buffer
        putChar('\n');
        IFS1bits.AD1IF == 0;                        // depois da leitura sempre!!
    }
    return 0;
}