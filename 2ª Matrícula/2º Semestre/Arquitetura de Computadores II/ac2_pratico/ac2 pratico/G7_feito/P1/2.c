#include <detpic32.h>
// variaveis char só dá para somar variaveis até 256
// NAO ESQUECER DE CONFIGURAR OS DISPLAYS SENÃO NAO VOU VER NADA POR mAIS BEm FEITA QUE AS FUNCOES ESTEJAm FEITAS
// PONTO E VIRGULA DEPOIS DO FOR É DESTRUTIVO
volatile unsigned char voltage = 0;         // Global variable 

void ConfigIO()
{
    TRISB = TRISB & 0x80FF;     // configure RB8-RB14 as outputs
    LATB = LATB & 0x80FF;       // coloca-los a 0, começam apagados
    TRISD = TRISD & 0xFF9F;     // configure RD5-RD6 as outputs
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
    AD1CON2bits.SMPI = 8-1;     // Interrupt is generated after N samples
                                // (replace N by the desired number of
                                // consecutive samples)
    AD1CHSbits.CH0SA = 4;       // replace x by the desired input
                                // analog channel (0 to 15)
    AD1CON1bits.ON = 1;         // Enable A/D converter (se nao for feito, o ADC nao funciona)
                                // This must the last command of the A/D
                                // configuration sequence 
}

void Config_Interrupts()
{
    IPC6bits.AD1IP = 2;         // configure priority of A/D interrupts
    IFS1bits.AD1IF = 0;         // clear A/D interrupt flag
    IEC1bits.AD1IE = 1;         // enable A/D interrupts
    EnableInterrupts();         // Macro defined in "detpic32.h"
}

 void send2displays(unsigned char value);
 void delay(unsigned int ms);

 unsigned char toBcd(unsigned char value)
{
    return ((value / 10) << 4) + (value % 10);
}

int main(void)
 {
    unsigned int cnt = 0;
    ConfigIO();
    Config_ADC();
    Config_Interrupts();            // Configure all (digital I/O, analog input, A/D module)
    while(1)      
    {
        if(cnt == 0)                // 0, 200 ms, 400 ms, ... (5 samples/second)
        {
            AD1CON1bits.ASAM = 1;            // Start A/D conversion
        }
        send2displays(voltage);              // Send "voltage" value to displays
        cnt = (cnt + 1) % 20;                // isto esta a incrementar o contador e simultaneamente a fazer o reset do mesmo, cada vez que o cnt for multiplo de 20, o resto da 0
        // vai fazer o while 20(á medida que incremente o cnt )x10ms, 5x por/seg. 
        // 1 contagem até 20 - 200ms, 5 x 200 ms = 1 seg. FReq = 5 Hz
        delay(10);                            // refrescamento de 10 ms para os displays, freq de 100Hz
    }             
    return 0;
 } 

 // Interrupt Handler, funcoes void indica que nao retornam nada
 void _int_(27) isr_adc(void)                       // Replace VECTOR by the A/D vector
 {
        int soma=0,tensao=0,media=0;

        int i;
                                                    // fazer conversao para tensao para armazenar na variavel voltage
        int *p = (int *)(&ADC1BUF0);                // read conversion result, a partir do endereco inicial

        for (i = 0; i < 8; i++)
        {
            soma += p[i*4];                         // ler os valores das amostras
        }
        media = soma/8;
        tensao = (media*33 + 511)/1023;   
        voltage = toBcd(tensao);                    // converter para decimal         

        IFS1bits.AD1IF = 0;                         // Reset AD1IF flag
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

void delay(unsigned int ms)
{
    int K = ms*20000;
    resetCoreTimer();
    while(readCoreTimer() < K);
}
