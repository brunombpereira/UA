#include <detpic32.h>


typedef struct t_buf
{
    char mem[100];              // Storage area
    int nchar;                  // Number of charecters to be transmittes
    int posrd;                  // Position of the next character to be transmitted
};


volatile t_buf txbuf;


int main(void) {
    U2BRG = (20000000 + 8 * 115200) / (16 * 115200) - 1;
    U2MODEbits.BRGH = 0;
    U2MODEbits.PDSEL = 0;
    U2MODEbits.STSEL = 0;
    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;
    U2MODEbits.ON = 1;

    IEC1bits.U2RXIE = 0;
    IEC1bits.U2TXIE = 0;
    IPC8bits.U2IP = 1;
    U2STAbits.UTXISEL = 0;
    EnableInterrupts();

    txbuf.nchar = 0;

    while (1)
    {
        putstrInt("Test string which can be as you like, up to a maximum of 100 characters\n");
    }
    return 0;
}


void _int_(32) isr_uart2(void) {
    if (IFS1bits.U2TXIF == 1)
    {
        if (txbuf.nchar > 0)
        {
            U2TXREG = txbuf.mem[txbuf.posrd];

            txbuf.posrd ++;
            txbuf.nchar --;
        } else
        {
            IEC1bits.U2TXIE = 0;
        }
        IFS1bits.U2TXIF = 0;        
    }
    
}