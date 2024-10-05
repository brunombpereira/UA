#include <detpic32.h>
void putc(char byte);
char getc(void);

int main(void){
	U2BRG = ((20000000 + (8 * 115200))/(16*115200))-1;
	
	U2MODEbits.BRGH = 0;			//FATOR DE DIVISAO DE 16
	
	U2MODEbits.PDSEL = 0;			// 8-bit data, no parity
	U2MODEbits.STSEL = 0;			// 1 stop bit
	
	U2STAbits.URXEN = 1;			// Receiver Enable bit
	U2STAbits.UTXEN = 1;			// Transmit Enable bit
	
	U2MODEbits.ON = 1;			// Enable UART2
	
	while(1){
		char c = getc();
		putc(c);
	}
	return 0;
}

char getc(void){
	while(U2STAbits.URXDA==0);		
	return U2RXREG;
}

void putc(char byte){
	while(U2STAbits.UTXBF==1);
	U2TXREG = byte;
}
