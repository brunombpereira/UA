#include <detpic32.h>


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