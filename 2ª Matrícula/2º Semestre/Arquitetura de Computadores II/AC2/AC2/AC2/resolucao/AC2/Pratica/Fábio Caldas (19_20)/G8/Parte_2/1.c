#include <detpic32.h>

#define fpbclk 20000000

void delay(int ms);
void putc(char byte2send);
void putStr(char *str);
char getc(void);

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

	if(stopbits == 1)
		U1MODEbits.STSEL = 0; //1 stop bit
	else if(stopbits == 2)
		U1MODEbits.STSEL = 1; //2 stop bit
	else
		U1MODEbits.STSEL = 0;


	U1STAbits.UTXEN = 1; //Transmitter enable
	U1STAbits.URXEN = 1; //Reciever enable

	U1MODEbits.ON = 1; //Enable UART1

	//Interrupt config UART1
	U1STAbits.URXISEL = 0;	//RX interrupt enable

	IPC6bits.U1IP = 2;		//Priority
	IEC0bits.U1RXIE = 1;	//Enable
	IFS0bits.U1RXIF = 0;	//Reset
}

int main(void)
{
	configUART1(115200,'N',1);

	EnableInterrupts();

	while(1)
	{

	}

	return 0;
}

void _int_(24) isr_uart1(void)
{
	putc(U1RXREG);
	IFS0bits.U1RXIF = 0;
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

char getc(void)
{
	char clear;
	if(U1STAbits.OERR == 1)
		U1STAbits.OERR = 0;
	while(U1STAbits.URXDA == 0);

	if(U1STAbits.FERR || U1STAbits.PERR)
	{
		clear = U1RXREG;
		return 0;
	} else
		return U1RXREG;
}

void delay(int ms)
{
	for(; ms > 0; ms--)
	{
		resetCoreTimer();
		while(readCoreTimer() < 20000);
	}
}
