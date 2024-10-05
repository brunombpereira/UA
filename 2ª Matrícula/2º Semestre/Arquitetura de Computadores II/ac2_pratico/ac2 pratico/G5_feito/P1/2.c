#include <detpic32.h>
void send2displays(unsigned char value);
// ISTO E COmO NAO SE FAZ, NAO HA TOGGLE ENTRE DISPLAYS
int main(void)
 {
    TRISB = TRISB & 0x80FF;     // configure RB8-RB14 as outputs
    TRISD = TRISD & 0xFF9F;     // configure RD5-RD6 as outputs
    while(1)
    {
      send2displays(0x15);       // quero mesmo que apareça 1 num diplay e 5 no outro
      resetCoreTimer();          // wait 0.2s
      while(readCoreTimer() < 4000000);
    }
 } 

 void send2displays(unsigned char value)
 {
    static const char display7Scodes[] = {0x3F, 0x06,0x5b,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
    LATDbits.LATD6 = 1;                   // select display high
    LATDbits.LATD5 = 0;
    int dh,dl,low,high;
    // o shift e para colocar o valor entre 0 e 15, se nao fizesse >> 4, o programa ia ao array display7Scodes buscar um valor entre 16-256
    dh = (value & 0x00F0) >> 4;           // send digit_high (dh) to display: dh = value >> 4, com os bits mais significativos, fico só com o 1 do value
    high = display7Scodes[dh];
    LATB = (LATB & 0x80FF) | (high << 8); // o high esta nos bits 7-4, fazemos shift de 8 para os colocar nos 15-12
    LATDbits.LATD6 = 0;                   // select display low
    LATDbits.LATD5 = 1;                    
    dl = value & 0x0F;                    // send digit_low (dl) to display: dl = value & 0x0F, com os bits menos significativos
    low = display7Scodes[dl];
    LATB = (LATB & 0x80FF) | (low << 8);
}


