#include <detpic32.h>


int main(void) {
    U2BRG = (20000000 + 8 * 115200) / (16 * 115200) - 1;
    U2MODEbits.BRGH = 0;
    U2MODEbits.PDSEL = 0;
    U2MODEbits.STSEL = 0;
    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;
    U2MODEbits.ON = 1;

    IPC8bits.U2IP = 1;
    IEC1bits.U2RX = 1;
    IEC1bits.U2TX = 0;
    IFS1bits.U2RXIF = 0;
    U2STAbits.URXISEL = 0;
    EnableInterrupts();

    TRISCbits.TRISC14 = 0;
    LATCbits.LATC14 = 0;

    while(1);
    return 0;
}


void _int_(32) isr_uart2(void) {
    if (IFS1bits.U2RXIF == 1)
    {
        char c = U2RXREG
        if (c == 'T')
        {
            LATCbits.LATC14 = 1;
        } else if (c == 't')
        {
            LATCbits.LATC14 = 0;
        }       
        IFS1bits.U2RXIF == 0;
    }
}