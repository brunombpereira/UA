#include <detpic32.h>
void putc1(char byte);

int main(void){
	//UxBRG = (Fpbclk + 8 *baudrate)/(16*baudrate)-1;
	U1BRG = ((20000000 + (8 * 115200))/(16*115200))-1;
	

	U1MODEbits.BRGH = 0;							//fator de divisão de relógio 16
	U1MODEbits.PDSEL = 0;							//Sem paridade
	U1MODEbits.STSEL = 0;							//1 stop bit

	U1STAbits.UTXEN = 1;							//Transmitter enable
	U1STAbits.URXEN = 1;							//Reciever enable

	U1MODEbits.ON = 1;							//Enable UART2
	
	while(1){
		putc('+');
		resetCoreTimer();
		while(readCoreTimer()<20000000);
	}
	
	return 0;
}

void putc1(char byte){
	while (U1STAbits.UTXBF==1);
	U1TXREG= byte;
}
