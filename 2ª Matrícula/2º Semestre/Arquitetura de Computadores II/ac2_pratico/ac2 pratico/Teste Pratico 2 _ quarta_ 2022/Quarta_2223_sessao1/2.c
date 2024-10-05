#include <detpic32.h>

volatile unsigned int temperatura;

void Config_Timer()
{
    T3CONbits.TCKPS = 2;            // 1:4 prescaler f_out = 140Hz
    PR3 = 35714;                    // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz 
    TMR3 = 0;                       // Reset timer T2 count register 
    T3CONbits.TON = 1;              // Enable timer T2 (must be the last command of the 
}

void Config_Interrupts()
{
    IPC3bits.T3IP = 2; // Interrupt priority (must be in range [1..6]) 
    IEC0bits.T3IE = 1; // Enable timer T2 interrupts 
    IFS0bits.T3IF = 0; // Reset timer T2 interrupt flag

    EnableInterrupts(); 
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

unsigned char to_Bcd(unsigned char value)
{
    return((value/10)<<4) + (value % 10);
}

void Config_ADC()
{
    TRISBbits.TRISB4 = 1; 
    AD1PCFGbits.PCFG4= 0; 
    AD1CON1bits.SSRC = 7; 
   
    AD1CON1bits.CLRASAM = 1;  
    
    AD1CON3bits.SAMC = 16; 
    AD1CON2bits.SMPI = 2-1;             // 2 conversões por amostra
     
    AD1CHSbits.CH0SA = 4;  
    
    AD1CON1bits.ON = 1;  
}

int main (void)
{
    Config_ADC();
    Config_Timer();
    Config_Interrupts();
    
    TRISB = TRISB & 0x80FF;             // configuração dos displays como saídas
    LATB = LATB & 0x80FF;               // começam apagados
    TRISD = TRISD & 0xFF9F;             // RD5 e RD6 como saídas, para selecionar cada um dos displays como um todo

    while(1)
    {
        AD1CON1bits.ASAM = 1;           // dar o início de conversão
        int soma = 0, media = 0, i;

        while(IFS1bits.AD1IF == 0);
        int *p = (int*)(&ADC1BUF0);
        for(i=0;i<2;i++)
        {
            soma += p[i*4];
        }
        media = soma/2;
        temperatura = (media*65 + 511)/1023 + 10;
        
        printInt10(temperatura);
        putChar('\n');
    
        resetCoreTimer();
        while(readCoreTimer() < 4000000);            // freq. amostragem de conversão a cada 5Hz
        soma = 0;
        media = 0;
        IFS1bits.AD1IF = 0;
    }
}

void _int_(12) isr_T3(void)                         // Replace VECTOR by the A/D vector 
 { 
    send2displays(to_Bcd(temperatura));
    IFS0bits.T3IF = 0; 		                        // Reset T3IF flag 
 } 
