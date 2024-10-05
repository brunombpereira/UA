#include <detpic32.h>


typedef struct t_buf
{
    char mem[100];
    int nchar;
    int posrd;
};


volatile t_buf txbuf;


void putstrInt(char *s) {
    while(txbuf.nchar > 0);

    while (*s |= '\0')
    {
        txbuf.mem[txbuf.nchar] = *s;
        s++;
        txbuf.nchar++;
    }

    txbuf.posrd = 0;
    IEC1bits.U2TXIE = 1;
    
}
