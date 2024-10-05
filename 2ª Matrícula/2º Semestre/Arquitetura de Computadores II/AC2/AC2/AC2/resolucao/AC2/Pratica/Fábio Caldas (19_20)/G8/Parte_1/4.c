#include <detpic32.h>

#define fpbclk 20000000

void putc(char byte2send);
void putStr(char *str);
void delay(int ms);

void configUART1(unsigned int baudrate, char parity, unsigned int stopbits)
{
	if(baudrate >= 600 && baudrate <= 115200)
		U1BRG = (fpbclk +8*baudrate)/(16*baudrate)-1; //config BaudRate generator
	else
		U1BRG = (fpbclk +8*115200)/(16*115200)-1;

	U1MODEbits.BRGH = 0; //divisão por 16

	switch(parity)
	{
		case 'N':
			U1MODEbits.PDSEL = 0; //Sem paridade
			break;

		case 'E':
			U1MODEbits.PDSEL = 1; //Par
			break;

		case 'O':
			U1MODEbits.PDSEL = 2; //Ímpar
			break;

		default:
			U1MODEbits.PDSEL = 0;
			break;
	}

	if(stopbits == 1 || stopbits == 2)
	{
		U1MODEbits.STSEL = stopbits-1;
	} else
	{
		U1MODEbits.STSEL = 0;
	}

	U1STAbits.UTXEN = 1; //Transmitter enable
	U1STAbits.URXEN = 1; //Reciever enable

	U1MODEbits.ON = 1; //Enable UART1
}

int main(void)
{
	configUART1(115200, 'N', 1);

	while(1)
	{
		putStr("String de teste\n");
		delay(1000);
	}

	return 0;
}

void putc(char byte2send)
{
	while(U1STAbits.UTXBF == 1);
	U1TXREG = byte2send;
}

void putStr(char *str)
{
	while(*str != '\0')
		putc(*str++);
}

void delay(int ms)
{
	for(; ms > 0; ms--)
	{
		resetCoreTimer();
		while(readCoreTimer() < 20000);
	}
}
