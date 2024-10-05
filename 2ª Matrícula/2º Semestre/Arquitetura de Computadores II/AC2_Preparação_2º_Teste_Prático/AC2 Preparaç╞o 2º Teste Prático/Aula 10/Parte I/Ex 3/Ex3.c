#include <detpic32.h>


void delay(unsigned int value);
void putc(char byte);


int main(void) {
    U2BRG = (20000000 + 8 * 115200) / (4 * 115200) - 1;
    U2MODEbits.BRGH = 0;
    U2MODEbits.PDSEL = 0;
    U2MODEbits.STSEL = 0;
    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;
    U2MODEbits.ON = 1;

    while(1) {
        putc('+');
        delay(1000);
    }

    return 0;
}


void putc(char byte) {
    while(U2STAbits.UTXBF == 1);
    U2TXREG = byte;
}


void delay(unsigned int ms) {
    int k = 20000 * ms;
    resetCoreTimer();
    while(readCoreTimer() < k);
}