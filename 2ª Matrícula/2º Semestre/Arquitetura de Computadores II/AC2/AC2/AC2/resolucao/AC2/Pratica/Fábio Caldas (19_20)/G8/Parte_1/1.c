#include <detpic32.h>

#define fpbclk 20000000
#define baudrate 115200

void configUART1()
{
	U1BRG = (fpbclk +8*baudrate)/(16*baudrate)-1;	//config BaudRate generator

	U1MODEbits.BRGH = 0;							//fator de divisão de relógio 16
	U1MODEbits.PDSEL = 0;							//Sem paridade
	U1MODEbits.STSEL = 0;							//1 stop bit

	U1STAbits.UTXEN = 1;							//Transmitter enable
	U1STAbits.URXEN = 1;							//Reciever enable

	U1MODEbits.ON = 1;								//Enable UART1
}

int main(void)
{
	configUART1();

	return 0;
}