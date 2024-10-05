#include <detpic32.h>

#define fpbclk 20000000
#define baudrate 115200

void putc(char byte2send);
void delay(int ms);

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

	while(1)
	{
		putc('+');
		delay(1000);
	}

	return 0;
}

void putc(char byte2send)
{
	while(U1STAbits.UTXBF == 1);
	U1TXREG = byte2send;
}

void delay(int ms)
{
	for(; ms > 0; ms--)
	{
		resetCoreTimer();
		while(readCoreTimer() < 20000);
	}
}
