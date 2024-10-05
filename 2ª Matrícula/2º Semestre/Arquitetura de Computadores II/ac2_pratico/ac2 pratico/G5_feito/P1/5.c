// Escreva um programa que implemente um contador ascendente módulo 256. O contador
// deve ser incrementado com uma frequência de 5 Hz e o seu valor deve ser mostrado nos
// dois displays em hexadecimal. A frequência de refrescamento do sistema de visualizacao
// deve ser 50 Hz
#include <detpic32.h>

int main(void)
 {
    int counter, i;                         // declare variables
    TRISB = TRISB & 0x80FF;                 // initialize ports
    LATB = LATB & 0x80FF;
    TRISD = (TRISD & 0xFF9F) | 0x0060;

    counter = 0;
    while(1)
    {
        i = 0;
    do{
        send2displays(counter);
        resetCoreTimer();       
        while(readCoreTimer() < 400000);    // wait 20 ms (1/50Hz) -> 400 000 - Resfrescamento

    } while(++i < 10);                       // acho que deve ser 10 pois, 20ms * 10 = 200ms, este valor é o que vai controlar a freq. do counter
                                             // ao fim de 200 ms o counter é incrementado, e neste loop com este valor conseguimos counter++5x por seg(5hz)
    if(counter < 256)
        counter++;                          // increment counter (mod 256)
    else
        counter = 0;
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