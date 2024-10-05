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

void comDrv_flushRx(void)
{
	rxb.head = 0;
	rxb.tail = 0;
	rxb.count= 0;
}

void comDrv_flushTx(void)
{
	txb.head = 0;
	txb.tail = 0;
	txb.count= 0;
}

void comDrv_putc(char ch){

	while(tbx.count == BUF_SIZE);
	txb.data[txb.tail] = ch;						//copia para o buffer o ch
	
	//secçao critica para incrementar o count que pode ser alterado ao mesmo tempo noutros lados
	DisableUart1TxInterrupt();
	txb.count ++;
	EnableUart1TxInterrupt();
	//fim
	txb.head = ( txb.head +1 ) & INDEX_MASK; 	//incrementa o head com uma mascara
		
}
