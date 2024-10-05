#include <detpic32.h>

#define DisableUart1RxInterrupt() IEC0bits.U1RXIE = 0
#define EnableUart1RxInterrupt()  IEC0bits.U1RXIE = 1
#define DisableUart1TxInterrupt() IEC0bits.U1TXIE = 0
#define EnableUart1TxInterrupt()  IEC0bits.U1TXIE = 1

#define BUF_SIZE 8
#define INDEX_MASK (BUF_SIZE -1)
typedef struct			//tipo classes em java
{
	unsigned char data[BUF_SIZE];
	unsigned int head;
	unsigned int tail;
	unsigned int count;
}circularBuffer;

volatile circularBuffer txb;
volatile circularBuffer rxb;

int comDrv_config( unsigned int buad, char parity,unsigned int stopbits){
	int flag=0;	


	if (buad<600 || buad >115200) {

		U1MODEbits.BRGH=0; 					//config baudrate  //taxa transm =16 logo->0
		U1BRG=10;

		flag=1;
	}
	else{
		U1MODEbits.BRGH=0; 					//config baudrate  //taxa transm =16 logo->0
		U1BRG = ((20000000+8*buad) / (16*buad)) - 1;
		LATB = (LATB & 0x00FF) | 7 << 8;
	}

	if (parity != 'E' && parity != 'N' && parity != 'O') {

		U1MODEbits.PDSEL=0;					//paridade: sem paridade

		LATB = (LATB & 0x00FF) | 3 << 8;
		flag=1;
	}
	else{
		//	LATB = (LATB & 0x00FF) | 2 << 8;
		if(parity == 'E' ){
			U1MODEbits.PDSEL = 1;			//paridade: par
		}
		else 	if(parity == 'N' ){
			U1MODEbits.PDSEL = 0;			//paridade: sem paridade
		}
		else 	if(parity == 'O' ){
			U1MODEbits.PDSEL = 2;			//paridade: impar
		}

	}

	if(stopbits != 1 && stopbits !=2){
		U1MODEbits.STSEL=0;					//nº Stop bits=1
		flag=1;
	}
	else{
		U1MODEbits.STSEL = stopbits-1;	//nº Stop bits=stopbits
	}


	U1STAbits.UTXEN = 1;						//ativar modulos de transmissao
	U1STAbits.URXEN = 1;						//ativar modulos de recessao

	U1MODEbits.ON = 1;						//ativar UART

	U1STAbits.URXISEL = 0; 					// Enable UART receive interrupt mode
	U1STAbits.UTXSEL = 0; 					// Enable UART trsnamit interrupt mode 
				//está a zero pq nao queremos que ele comece logo a gerar interrupçoes

	IPC6bits.U1IP = 2;		 				// Interrupt priority (must be in range [1..6])
	IEC0bits.U1RXIE = 0;				   	// Enable UART interrupts 
	IEC0bits.U1TXIE = 0;				   	// Enable UART interrupts


	IFS0bits.U1RXIF = 0;	 					// Reset UART interrupt flag
	IFS0bits.U1TXIF = 0;	 					// Reset UART interrupt flag


	return flag;
}

int main(void){
	comDrv_config(115200,'N', 1);

	comDrv_flushRx();
	comDrv_flushTx();
	EnableInterrupts();	
	while(1)
		comDrv_puts( " Teste do bloco de transmissao do device driver!.." );
	return 0;
}


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
	//como metemos um char ha coisas para transmitir logo temos de dar enable da interrupçao de transmissao
}

char comDrv_getc(char *pchar)
{
	if(count == 0 ) return FALSE;

	DisableUart1RxInterrupt();	
  	
	*pchar= rxb.data[rxb.head];
	
	rxb.count = (rxb.count - 1);
	rxb.head = (rxb.head + 1) & INDEX_MASK; 
	
	EnableUart1RxInterrupt();	
	return TRUE;
}
void comDrv_puts(char *s){
	while( *s != '\0'){
		comDrv_putc(*s);
		s++;
	}
}

void _int_(24) isr_uart1(void){
	if(IFS0bits.U1TXIF == 1){
		if( txb.count > 0){
			U1TXREG = txb.data[txb.head];
			txb.head = (txb.head + 1) & INDEX_MASK; 
			txb.count = (txb.count - 1);
		}
		if(txb.count == 0 ) {
			DisableUart1TxInterrupt();						// quando nao ha mais nada para tranmitir nao é preciso
																	// haver mais interrupçoes
		}
		IFS0bits.U1TXIF = 0; 

	}
}

