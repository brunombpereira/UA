#include <detpic32.h> 
// configurações usando estruturas 
void delay(unsigned int ms)

int main(void) 
 { 
    unsigned char segment;              // x x x x  x 0 1 x  x x x x 
    int i;
    TRISDbits.TRISD5 = 0;               // configurar RD5 e RD6 como saídas 
    TRISDbits.TRISD6 = 0;
    TRISB = TRISB & 0x80FF;             // configure RB8-RB14 as outputs 
    LATB = LATB & 0x80FF;               // começar com os segmentos todos desligados
    LATDbits.LATD5 = 1;                 // selecionar o display menos significiativo
    LATDbits.LATD6 = 0;

    while(1) 
    { 
    segment = 1; 
    for(i=0; i < 7; i++) 
    { 
        LATB = (LATB & 0x80FF) | (segment << 8);  // send "segment" value to display 
        delay(500);                               // wait 0.5 second 
        segment = segment << 1; 
    } 
        LATDbits.LATD5 = ! LATDbits.LATD5;        // toggle display selection 
        LATDbits.LATD6 = ! LATDbits.LATD6;
    } 
    return 0; 
 } 

 void delay(unsigned int ms)
 {
    int K = 20000*ms;
    resetCoreTimer();
    while(readCoreTimer() < K);
 }
