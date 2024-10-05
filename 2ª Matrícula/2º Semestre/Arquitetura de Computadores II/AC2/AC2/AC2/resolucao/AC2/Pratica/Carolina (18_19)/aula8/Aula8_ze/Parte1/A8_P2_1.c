#include <detpic32.h>

void putc(char);
void delay(int);

int main(void)
{
	// Configure UART1:
	// 1 - Configure BaudRate Generator
	U1MODEbits.BRGH = 0;	// 16

	// 2 – Configure number of data bits, parity and number of stop bits
	//(see U1MODE register)
	U1BRG = 10;				// Counter compare thingy
	U1MODEbits.PDSEL = 0;	// 8 bits, no parity
	U1MODEbits.STSEL = 0;	// 1 stop bit

	// 3 – Enable the trasmitter and receiver modules (see register U1STA)
	U1STAbits.UTXEN = 1;	// Enable transmitter
	U1STAbits.URXEN = 1;	// Enable receiver

	// 4 – Enable UART1 (see register U1MODE)
	U1MODEbits.ON = 1; 		// Enable UART


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

