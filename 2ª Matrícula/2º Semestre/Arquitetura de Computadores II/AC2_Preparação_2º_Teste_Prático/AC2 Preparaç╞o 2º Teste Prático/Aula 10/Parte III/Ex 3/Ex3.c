#include <detpic32.h>


void putC(char byte);
void putStr(char *str);


int main(void) {
    U2BRG = (20000000 + 8 * 115200) / (16 * 115200) - 1;
    U2MODEbits.BRGH = 0;
    U2MODEbits.PDSEL = 0;
    U2MODEbits.STSEL = 0;
    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;
    U2MODEbits.ON = 1;

    TRISDbits.TRISD11 = 0;
    LATDbits.LATD11 = 0;

    while (1)
    {
        // while(U2STAbits.TRMT == 0);
        LATDbits.LATD11 = 1;
        putStr("12345");
        LATDbits.LATD11 = 0;
    }
    return 0;
}


void putC(char byte) {
    while(U2STAbits.UTXBF == 1);
    U2TXREG = byte;
}


void putStr(char *str) {
    while (*str != '\0')
    {
        putC(*str);
        str ++;
    }
}