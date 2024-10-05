#include <detpic32.h>



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

int main (void){
	U1MODEbits.BRGH == 0 ;		//taxa =16
	U1BRG = 10;

	U1MODEbits.PDSEL = 0;		//sem paridade
	U1MODEbits.STSEL = 0 ;		//1 stop bit
	
	U1STAbits.UTXEN = 1;
	U1STAbits.UTXEN = 1;
	U1MODEbits.ON = 1;

	while(1){
		putc('+');
		delay(1000);
	}
return 0;
}


