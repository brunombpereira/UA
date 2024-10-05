// contador módulo 60 com o sentido de contagem dependente do valor lógico 
// imposto pelo dip-switch 1 (DS1, ligado ao porto RB0): ON – contagem ascendente, OFF – 
// contagem descendente
#include <detpic32.h>

void send2displays(unsigned char value)
unsigned char toBcd(unsigned char value)

int main(void)
{
    int counter, i;                         // declare variables
    TRISB = (TRISB & 0x80FF) | 0x0001;      // initialize ports, RB1 como entrada
    LATB = LATB & 0x80FF;
    TRISD = (TRISD & 0xFF9F) | 0x0060;

    counter = 0;
    while(1)
    {
        i = 0;
    do{
        send2displays(toBcd(counter));
        resetCoreTimer();       
        while(readCoreTimer() < 200000);    // wait 10 ms (1/100Hz) -> 200 000 - Resfrescamento

    } while(++i < 50);                      // 100 varrimentos de 10ms cada = 1000ms = 1seg, faria o counter++ a cada 1seg
                                            // colocar 50 para que 50 varrimentos * 10ms cada = 500 ms, e o counter seja incrementado 2x por seg
    if(PORTBbits.PORTB0 = 1){
        if(counter < 59)
            counter++;                          // increment counter (mod 60), se counter = 59 dar reset
        else
            counter = 0;
    }  
    else{
        if(counter > 0)
        counter--;                          // increment counter (mod 60), se counter = 59 dar reset
        else
        counter = 59;
    }
    }
    return 0;
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