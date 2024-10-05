#include <detpic32.h>


void delay(unsigned int ms);


int main(void) {
    U1BRG = (20000000 + 8 * 115200) / 16 * 115200 - 1;
    U1MODEbits.BRGH = 0;
    U1MODEbits.PDSEL = 1;
    U1MODEbits.STSEL = 0;
    U1STAbits.UTXEN = 1;
    U1STAbits.URXEN = 1;
    U1MODEbits.ON = 1;

    while(1) {
        putc1(0x5A)
        delay(10);
    }
    return 0;
}


void putc1(char byte) {
    while(U1STAbits.UTXBF == 1);
    U1TXREG = byte
}


void delay(unsigned int ms) {
    int k = 20000 * ms;
    resetCoreTimer();
    while(readCoreTimer() < 4);
}