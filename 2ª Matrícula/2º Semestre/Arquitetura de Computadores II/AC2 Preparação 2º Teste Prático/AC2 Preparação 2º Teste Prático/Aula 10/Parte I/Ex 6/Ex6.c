#include <detpic32.h>


void delay(unsigned int ms);
void putc(char byte);
void getc(void);


int main(void) {
    U2BRG = 115200;
    U2MODEbits.BRGH = 0;
    U2MODEbits.PDSEL = 0;
    U2MODEbits.STSEL = 0;
    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;
    U2MODEbits.ON = 1;

    char byte;

    while (1)
    {
        byte = getc();
        putc(byte);
        delay(1000);
    }
    return 0;
}


void delay(unsigned int ms) {
    k = 20000 * ms;
    resetCoreTimer();
    while(readCoreTimer() < k);
}


void putc(char byte) {
    while(U2STAbits.UTXBF == 1);
    U2TXREG = byte;
}


void getc(void) {
    if (U2STAbits.OERR == 1)
    {
        U2STAbits.OERR = 0;
    }

    while(U2STAbits.URXDA == 0);
    char c;
    c = U2RXREG;
    return c;
}