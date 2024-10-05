#include <detpic32.h>
void putc(char byte);
void putstr(char *str);
char getc(void);


int main(void){
	//UxBRG = (Fpbclk + 8 *baudrate)/(16*baudrate)-1;
	U2BRG = ((20000000 + (8 * 115200))/(16*115200))-1;
	

	U2MODEbits.BRGH = 0;							//fator de divisão de relógio 16
	U2MODEbits.PDSEL = 0;							//Sem paridade
	U2MODEbits.STSEL = 0;							//1 stop bit

	U2STAbits.UTXEN = 1;							//Transmitter enable
	U2STAbits.URXEN = 1;							//Reciever enable

	U2MODEbits.ON = 1;							//Enable UART2
	
	while(1){
		char request = getc();
		putc(request);
	}
	
	return 0;
}

char getc(void){
	if (U2STAbits.OERR == 1){
		U2STAbits.OERR = 0;
	}
	while(U2STAbits.URXDA==0);
	return U2RXREG;
}

void putc(char byte){
	while (U2STAbits.UTXBF==1);
	U2TXREG= byte;
}

void putstr(char *str){
	while(*str != '\0'){
		putc(*str++);
	}
}

