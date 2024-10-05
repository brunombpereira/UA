#include <detpic32.h>

#define DisableUart1RxInterrupt() IEC0bits.U1RXIE = 0
#define DisableUart1TxInterrupt() IEC0bits.U1TXIE = 0
#define EnableUart1RxInterrupt() IEC0bits.U1RXIE = 1
#define EnableUart1TxInterrupt() IEC0bits.U1TXIE = 1
#define BUF_SIZE	8
#define INDEX_MASK (BUF_SIZE -1)
typedef struct
{
	unsigned char data[BUF_SIZE];
	unsigned int head;
	unsigned int tail;
	unsigned int count;
}circularBuffer;

//instancias
volatile circularBuffer txb;
volatile circularBuffer rxb;
