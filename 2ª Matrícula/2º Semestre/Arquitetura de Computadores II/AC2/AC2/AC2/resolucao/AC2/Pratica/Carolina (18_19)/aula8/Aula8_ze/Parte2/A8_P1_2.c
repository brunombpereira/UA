#include <detpic32.h>


void putc(char);
void configUart(unsigned int, char, unsigned int);


void _int_(24) isr_uart1(void)
{

	putc(U1RXREG);	// Clear UART1 rx interrupt flag
	IFS0bits.U1RXIF = 0;	 // Reset UART interrupt flag
	
}


int main(void)
{

	configUart(115200,'N',1);	// default "pterm" parameters
								// with RX interrupt enabled

	EnableInterrupts();

	
	while(1);

	
	return 0;

}


void configUart(unsigned int baud, char parity, unsigned int stopbits)
{

	// Configure UART1:
	// 1 - Configure BaudRate Generator
	U1MODEbits.BRGH = 0;	// 16

	// 2 – Configure number of data bits, parity and number of stop bits
	//(see U1MODE register)

	// Counter compare thingy:
	if( (baud >= 600) && (baud <= 115200) ) 
	{

		U1BRG = ((20000000 + 8 * baud) / (16 * baud)) - 1;

	}
	
	else {U1BRG = 10;} // 10 = 115200 aka default
	
	// Parity:
	if(parity == 'E') 	  {U1MODEbits.PDSEL = 1;}
	else if(parity == 'O') {U1MODEbits.PDSEL = 2;}
	else 				  {U1MODEbits.PDSEL = 0;}

	// Stop bits:
	if(stopbits == 2) {U1MODEbits.STSEL = 1;}
	else			 {U1MODEbits.STSEL = 0;}				
	
	

	// 3 – Enable the trasmitter and receiver modules (see register U1STA)
	U1STAbits.UTXEN = 1;	// Enable transmitter
	U1STAbits.URXEN = 1;	// Enable receiver

	// 4 – Enable UART1 (see register U1MODE)
	U1MODEbits.ON = 1; 		// Enable UART




	U1STAbits.URXISEL = 0; // Enable UART receive interrupt mode

	IPC6bits.U1IP = 2;		 // Interrupt priority (must be in range [1..6])
	IEC0bits.U1RXIE = 1;	 // Enable UART interrupts
	IFS0bits.U1RXIF = 0;	 // Reset UART interrupt flag

}


void putc(char byte2send)
{

	while(U1STAbits.UTXBF == 1);

	U1TXREG = byte2send;

}

