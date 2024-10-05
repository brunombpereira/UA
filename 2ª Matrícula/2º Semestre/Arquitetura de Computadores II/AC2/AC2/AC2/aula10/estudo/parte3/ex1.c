#include <detpic32.h>


int main(void){
// Configurar UART2 115200, N, 8, 1

	//UxBRG = (Fpbclk + 8 *baudrate)/(16*baudrate)-1;
	U2BRG = ((20000000 + (8 * 115200))/(16*115200))-1;
	
	U2MODEbits.BRGH = 0;
	
	U2MODEbits.PDSEL = 0;			// 8-bit data, no parity
	U2MODEbits.STSEL = 0;			// 1 stop bit
	
	U2STAbits.URXEN = 1;			// Receiver Enable bit
	U2STAbits.UTXEN = 1;			// Transmit Enable bit
	
	U2MODEbits.ON = 1;			// Enable UART2
	
// Configurar o porto rd11
	TRISD = TRISD & 0xF7FF;		//1111 0111 1111 1111
	
	while(1){
		while(U2STAbits.TRMT==0);	//garantir que a uart nao tem informaçao a ser 						transmitida
		LATD = LATD & 0xF7FF;		// set rd11
		puts("12345");
		LATD = LATD & 0xF7FF;		//reset rd11
	
	}
	return 0;
}
