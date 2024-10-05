#include <detpic32.h> 
// configurações usando máscaras
void delay(unsigned int ms)

int main(void) 
 { 
    unsigned char segment;              // x x x x  x 0 1 x  x x x x 
    int i;
    TRISD = (TRISD & 0xFF9F);           // configurar RD5 e RD6 como saídas 
    TRISB = TRISB & 0x80FF;             // configure RB8-RB14 as outputs 
    LATB = LATB & 0x80FF;               // segmentos a zero no início    
    LATD = (LATD & 0xFF9F) | 0x0020;    // RD5 a 1, Rd6 a 0

    while(1) 
    { 
        segment = 1; 
        for(i=0; i < 7; i++) 
        { 
            LATB = (LATB & 0x80FF) | (segment << 8);  // send "segment" value to display 
            delay(500);                               // wait 0.5 second 
            segment = segment << 1; 
        } 
            LATD = LATD ^ 0x0060;   // toggle display selection - vai estar a negar constantemente o que estiver em RD5 RD6
    } 
    return 0; 
 } 

 void delay(unsigned int ms)
 {
    int K = 20000*ms;
    resetCoreTimer();
    while(readCoreTimer() < K);
 }