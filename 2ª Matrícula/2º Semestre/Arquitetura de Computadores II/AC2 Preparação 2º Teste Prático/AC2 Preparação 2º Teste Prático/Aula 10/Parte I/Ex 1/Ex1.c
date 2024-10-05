#include <detpic32.h>


int main(void) {
    U2BRG = (20000000 + 8 * 115200) / (16 * 115200);
    U2MODEbits.BRGH = 0;
    U2MODEbits.PDSEL = 0;
    U2MODEbits.STSEL = 0;
    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;
    U2MODEbits.ON = 1;

    while(1);
    return 0;
}