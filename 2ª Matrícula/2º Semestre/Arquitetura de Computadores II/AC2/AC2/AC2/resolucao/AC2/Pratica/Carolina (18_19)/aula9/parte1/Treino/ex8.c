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

	while(txb.count == BUF_SIZE);
	txb.data[txb.tail] = ch;						//copia para o buffer o ch
	
	//secçao critica para incrementar o count que pode ser alterado ao mesmo tempo noutros lados
	DisableUart1TxInterrupt();
	txb.count = (txb.count + 1 );
	EnableUart1TxInterrupt();
	//fim
	txb.tail = ( txb.tail +1 ) & INDEX_MASK; 	//incrementa o head com uma mascara
		
}

void comDrv_puts( char *s){
	while( *s != '\0'){
		comDrv_putc(*s);
		s++;
	} 
}

void _int_(24) isr_uart1(void){
	if(IFS0bits.U1TXIF == 1 ){		//se a flag de interrupçao de transmiçao
		if(txb.count > 0 ) 			//se houver algo para transmitir
		{
			U1TXREG = txb.data[txb.head];				
			txb.head = ( txb.head + 1 ) & INDEX_MASK; 	//incrementa o head com uma mascara
			txb.count=(txb.count - 1 );
		}
		if(txb.count == 0){
				DisableUart1TxInterrupt();
		}
		IFS0bits.U1TXIF = 0;					//reset interr flag
	}
	if(IFS0bits.U1RXIF == 1) {
		rxb.data[rxb.tail] = U1RXREG;
		rxb.tail = (rxb.tail+1) & INDEX_MASK;
		if(rxb.count == BUF_SIZE){
			rxb.head = (rxb.head +1) & INDEX_MASK;
		}
		else{
			rxb.count = (rxb.count+1);
		}
		IFS0bits.U1RXIF == 0;				//reset inter flag
	}
}
#define FALSE 0;
#define TRUE 1;

char comDrv_getc(char *pchar){

	if(rxb.count == 0){
		return FALSE;
	}
	else{
		DisableUart1RxInterrupt();
		*pchar = rxb.data[rxb.head];
		rxb.head = (rxb.head + 1 ) &	INDEX_MASK;
		rxb.count = rxb.count-1;
		EnableUart1RxInterrupt();
		return TRUE;
	}
}

int main(void){

	U1MODEbits.BRGH = 0;		//taxa 16 
	U1BRG = 10;

	U1MODEbits.PDSEL = 0;		//sem paridade
	U1MODEbits.STSEL = 0;	//stop bits

	U1STAbits.URXEN = 1;		//ativar modos de recessao
	U1STAbits.UTXEN = 1;		//ativar modos de transmissao

	U1MODEbits.ON = 1;			//ativar uart

	//interrupçoes

	IPC6bits.U1IP = 2; 		//prioridade
	
	EnableUart1RxInterrupt();
	DisableUart1TxInterrupt();
	
	IFS0bits.U1RXIF = 0;		//reset da uart interrupt flag
	IFS0bits.U1TXIF = 0;
		
	comDrv_flushRx();
	comDrv_flushTx();
	EnableInterrupts();
	comDrv_puts("PIC32 UART Bevice-driver\n");
	char ch;
	while(1){
		comDrv_putc(comDrv_getc(&ch));
	}
			return 0;
}
