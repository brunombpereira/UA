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
			U1TXREG = txb.head;				
			txb.head = ( txb.head + 1 ) & INDEX_MASK; 	//incrementa o head com uma mascara
			txb.cont++;
		}
		if(txb.count == 0){
			DisableUart1TxInterrupts();
		}
IEC0bits.U1TXIE = 0;
	}
}


int main(void){

	U1MODEbits.BHGH = 0;		//taxa 16 
	U1BRG = 10;

	U1MODEbits.PDSL = 0;		//sem paridade
	U1MODEbits.STSEL = 0;	//stop bits

	U1STAbits.URXEN = 1;		//ativar modos de recessao
	U1STAbits.UTXEN = 1;		//ativar modos de transmissao

	U1STAbits.ON = 1;			//ativar uart

	//interrupçoes

	IPC6bits.U1IP = 2 		//prioridade
	
	DisableUart1RxInterrupt() ;
	DisableUart1TxInterrupt(); 
	
	IFS0bits.U1RxIF = 0;		//reset da uart interrupt flag
	IFS0bits.U1TxIF = 0;

	comDrv_flushRx();
	comDrv_flushTx();
	EnableInterrupts();
	while(1)
		comDrv_puts("TESTE DO BLOCO DE TRANSMISSAO DO DEVICE DRIVER!...");
	return 0;
}
