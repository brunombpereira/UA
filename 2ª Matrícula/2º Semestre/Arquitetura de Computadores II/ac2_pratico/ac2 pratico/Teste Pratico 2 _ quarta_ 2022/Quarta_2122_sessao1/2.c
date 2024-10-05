#include <detpic32.h>

volatile unsigned int temperatura;

void Config_Timers()
{
    T2CONbits.TCKPS = 2;         // 1:4 prescaler (i.e Fout_presc = 625 KHz) 
    PR2 = 41666;                 // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz 
    TMR2 = 0;                    // Reset timer T2 count register 
    T2CONbits.TON = 1;
}

void Config_Interrupts()
{
    IPC2bits.T2IP = 2;          // Interrupt priority (must be in range [1..6]) 
    IEC0bits.T2IE = 1;          // Enable timer T2 interrupts 
    IFS0bits.T2IF = 0;          // Reset timer T2 interrupt flag 
    EnableInterrupts();
}

void Config_IO()
{
    TRISB = TRISB & 0x80FF;         // segmentos dos displays como saídas e inicializados a 0
    LATB = LATB & 0x80FF;
    TRISD = TRISD & 0xFF9F;         // display high e low como saídas
}

unsigned char to_Bcd(unsigned char value)
{
    return((value/10)<<4) + (value % 10);
}

void send2displays (unsigned char value)
{
    static const char disp7Scodes[] ={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
    static char displayFlag = 0;

    int dh,dl,low,high;

    dh = (value & 0x00F0) >> 4;         // isolar cada caracter de 4 bits
    dl = value & 0x0F;

    if(displayFlag == 0)
    {
        LATDbits.LATD5 = 1;             // selecionar o display menos significativo
        LATDbits.LATD6 = 0;
        low = disp7Scodes[dl];
        LATB = (LATB & 0x80FF) | (low << 8);
    }
    else 
    {
        LATDbits.LATD5 = 0;             // selecionar o display mais significativo
        LATDbits.LATD6 = 1;
        high = disp7Scodes[dh];
        LATB = (LATB & 0x80FF) | (high << 8);
    } 
    displayFlag = !displayFlag;
}

void Config_ADC()   // freq. de conversão = 10 Hz
{
    TRISBbits.TRISB4 = 1; 
    AD1PCFGbits.PCFG4= 0; 
    AD1CON1bits.SSRC = 7; 
    
    AD1CON1bits.CLRASAM = 1; 
   
    AD1CON3bits.SAMC = 16; 
    AD1CON2bits.SMPI = 2-1; 

    AD1CHSbits.CH0SA = 4; 
    
    AD1CON1bits.ON = 1;
}

int main (void)
{
    Config_IO();
    Config_Timers();
    Config_Interrupts();
    Config_ADC();

    int soma = 0, media = 0;
    int i;

    while(1)
    {
        AD1CON1bits.ASAM = 1;                       // Start conversion, fim de conversão verificado por polling
        while(IFS1bits.AD1IF == 0);                 // quando a conversao acaba IFS1bits.AD1IF == 0 e colocado a 1 automaticamente, dai ser necessario 
                                                    // colocar a 0 manualmente no final do ciclo. se nao fica eternamente em estado de interrupcao
        int *p = (int*)(&ADC1BUF0);
        for(i=0;i<2;i++)
        {
            soma += p[i*4];
        }
        media = soma/2;
        temperatura = (media*50+511)/1023 + 15;

        printInt10(temperatura);
        putChar('\n');

        resetCoreTimer();
        while(readCoreTimer() < 2000000);           // frequência de conversão 10 Hz -> 100ms
        
        IFS1bits.AD1IF = 0;
        soma = 0;
        media = 0;
    }
    return 0;
}

void _int_(8) isr_T2(void)                          // Replace VECTOR by the timer T3 vector number 
 {  
    send2displays(to_Bcd(temperatura));
    IFS0bits.T2IF = 0; 
 }