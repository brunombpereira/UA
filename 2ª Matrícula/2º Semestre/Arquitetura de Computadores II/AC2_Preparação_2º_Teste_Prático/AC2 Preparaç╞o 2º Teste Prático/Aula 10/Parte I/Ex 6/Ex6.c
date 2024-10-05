#include <detpic32.h>


void delay(unsigned int ms);
void putc(char byte);
char getc(void);


int main(void) {
    U2BRG = (20000000 + 8 * 115200) / (16 * 115200) - 1;
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
    }
    return 0;
}


void putc(char byte) {
    while(U2STAbits.UTXBF == 1);
    U2TXREG = byte;
}


char getc(void) {
    if (U2STAbits.OERR == 1)
    {
        U2STAbits.OERR = 0;
    }

    while(U2STAbits.URXDA == 0);
    char c;
    c = U2RXREG;
    return U2RXREG;
}