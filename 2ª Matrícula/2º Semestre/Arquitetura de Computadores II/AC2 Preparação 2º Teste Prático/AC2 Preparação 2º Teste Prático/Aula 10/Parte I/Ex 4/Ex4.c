#include <detpic32.h>


void delay(unsigned int ms);
void putc(char byte);
void putstr(char *str);


int main(void) {
    U2BRG = 115200;
    U2MODEbits.BRGH = 0;
    U2MODEbits.PDSEL = 0;
    U2MODEbits.STSEL = 0;
    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;
    U2MODEbits.ON = 1;

    while (1)
    {
        putstr("String de teste\n");
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


void putstr(char *str) {
    while (*str != '\0')
    {
        putc(*str);
        str++;
    }
}