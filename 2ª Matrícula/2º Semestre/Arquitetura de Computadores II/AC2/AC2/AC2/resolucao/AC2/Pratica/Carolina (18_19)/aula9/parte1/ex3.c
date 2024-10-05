#include <detpic32.h>

#define DisableUart1RxInterrupt() IEC0bits.U1RXIE = 0
#define EnableUart1RxInterrupt()  IECObits.U1RXIE = 1
#define DisableUart1TxInterrupt() IEC0bits.U1TXIE = 0
#define EnableUart1TxInterrupt()  IECObits.U1TXIE = 1

typedef strut
{
	unsigned char data[8];
	unsigned int head;
	unsigned int tail;
	unsigned int count;
}circularBuffer;

volatile circularBuffer txb;
volatile circularBuffer rxb;

void comDrv_flushRx(void){
	rxb.head = 	0; 
	rxb.tail =	0;
	rxb.count = 0;

}

void comDrv_flushTx(void){
	txb.head = 	0; 
	txb.tail =	0;
	txb.count = 0;
}

