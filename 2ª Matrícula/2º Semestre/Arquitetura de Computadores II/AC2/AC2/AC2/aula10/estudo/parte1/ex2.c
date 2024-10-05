#include <detpic32.h>
void putc(char byte);

int main(void){
// Configurar UART 115200, N, 8, 1

	//UxBRG = (Fpbclk + 8 *baudrate)/(16*baudrate)-1;
	U2BRG = ((20000000 + (8 * 115200))/(16*115200))-1;
	
	U2MODEbits.BRGH = 0;
	
	U2MODEbits.PDSEL = 0;			// 8-bit data, no parity
	U2MODEbits.STSEL = 0;			// 1 stop bit
	
	U2STAbits.URXEN = 1;			// Receiver Enable bit
	U2STAbits.UTXEN = 1;			// Transmit Enable bit
	
	U2MODEbits.ON = 1;			// Enable UART2
	
	while(1){
		putc('+');
		resetCoreTimer();
		while(readCoreTimer()<20000000);
	
	}
	return 0;
}


void putc(char byte){
	while(U2STAbits.UTXBF==1);
	U2TXREG = byte;
}
