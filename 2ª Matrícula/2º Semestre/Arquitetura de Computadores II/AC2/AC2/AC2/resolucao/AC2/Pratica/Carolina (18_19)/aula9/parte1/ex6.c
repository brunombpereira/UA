#include <detpic32.h>

#define DisableUart1RxInterrupt() IEC0bits.U1RXIE = 0
#define EnableUart1RxInterrupt()  IECObits.U1RXIE = 1
#define DisableUart1TxInterrupt() IEC0bits.U1TXIE = 0
#define EnableUart1TxInterrupt()  IECObits.U1TXIE = 1

#define BUF_SIZE 8
#define INDEX_MASK (BUF_SIZE -1)
typedef strut			//tipo classes em java
{
	unsigned char data[BUF_SIZE];
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

void comDrv_putc(char ch){
	while(txb.count == BUF_SIZE){}						//espera que haja espaço livre no buffer
	txb.data[txb.tail] = ch;								//copy character to the transmission
																	//buffer at position tail
	txb.tail = (txb.tail +1) & INDEX_MASK; 			//incrementa "tail"
	DisableUart1TxInterrupt();								//begin of critical section
	txb.count = (txb.count +1);
	EnableUart1TxInterrupt();								//end of critical section

}

void comDrv_puts(char *s){
	while( *s =! '\0'){
		 comDrv_putc(*s);
		 s++;
	}
}

void _int_(24) isr_uart1(void){
	if(IFS0bits.U1TXIF == 1){
		if( txb.count > 0){
			U1TXREG = txb.head;
			txb.head = (txb.head + 1) & INDEX_MASK; 
			txb.count = (txb.count - 1);
		}
		if(txb.count == 0 ){
			DisableUart1TxInterrupt();		
		}
		IFS0bits.U1TXIF == 0; 
	
	}

}

