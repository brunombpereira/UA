#include <detpic32.h>

void putc(char byte2send);
void delay(unsigned int ms);


void putc(char byte2send){
	while(U1STAbits.UTXBF == 1);
	U1TXREG = byte2send;
}
void delay(unsigned int ms){
	for(; ms > 0 ; ms--)
	{
		resetCoreTimer();
		while (readCoreTimer() < 20000);
	}
}

void puts( char *s){
	while( *s != '\0'){
		putc(*s);
		s++;
	}
}

char getc(void){
	if(U1STAbits.OERR ==1)
		U1STAbits.OERR = 0 ; 
	while( U1STAbits.URXDA == 0);

	if(U1STAbits.FERR || U1STAbits.PERR){
		int lixo = U1RXREG; 		//descartar o valor lido
		return 0;
	}
	else return U1RXREG;
}



int main (void){
	U1MODEbits.BRGH == 0 ;		//taxa =16
	U1BRG = 10;

	U1MODEbits.PDSEL = 0;		//sem paridade
	U1MODEbits.STSEL = 0;		//1 stop bit

		U1STAbits.UTXEN = 1;
	U1STAbits.UTXEN = 1;
	U1MODEbits.ON = 1;

	while(1){
		putc(getc());
	}
	return 0;
}

