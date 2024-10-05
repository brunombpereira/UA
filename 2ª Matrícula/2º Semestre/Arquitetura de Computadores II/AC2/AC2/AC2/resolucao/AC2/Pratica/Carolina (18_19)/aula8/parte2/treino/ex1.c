#include <detpic32.h>
void putc( char byte2send);

void putc(char byte2send){
	while(U1STAbits.UTXBF == 1);	//sai qnd estiver vazio
	U1TXREG = byte2send;
}







void _int_(24) isr_uart1(void){
	putc(U1RXREG);
	IFS0bits.U1RXIF = 0;	
}

int main (void){
	U1MODEbits.BRGH == 0 ;		//taxa =16
	U1BRG = 10;

	U1MODEbits.PDSEL = 0;		//sem paridade
	U1MODEbits.STSEL = 0 ;		//1 stop bit

	U1STAbits.UTXEN = 1;
	U1STAbits.UTXEN = 1;
	U1MODEbits.ON = 1;
	
	IPC6bits.U1IP	=	2;			//definir prioridade
	IEC0bits.U1RXIE	=	1;		//fazer enable interrupt
	IFS0bits.U1RXIF	=	0;		//reset do interrupt flag
	//interrupções
	U1STAbits.URXISEL = 0;		// quero interrupção na receção
	
	EnableInterrupts();
	while(1);
	return 0;
}


