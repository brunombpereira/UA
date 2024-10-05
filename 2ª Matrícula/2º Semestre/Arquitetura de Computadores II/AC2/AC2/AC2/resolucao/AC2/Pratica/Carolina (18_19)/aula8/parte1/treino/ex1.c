#include <detpic32.h>

int main (void){
	U1MODEbits.BRGH == 0 ;		//taxa =16
	U1BRG = 10;

	U1MODEbits.PDSEL = 0:		//sem paridade
	U1MODEbits.STSEL = 0 :		//1 stop bit
	
	U1STAbits.UTXEN = 1;
	U1STAbits.UTXEN = 1;
	U1MODEbits.ON = 1;
}
