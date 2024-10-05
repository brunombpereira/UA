#include <detpic32.h>

void putc(char);
void puts(char *);
void configUart(unsigned int, char, unsigned int);
char getc(void);

int main(void)
{

	configUart(115200, 'N', 1);

	TRISB = (TRISB & 0xFFFDF);

	while(1)
	{

		 putc( getc() );
		
	}


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

}


void puts(char *str)
{

	int i;

	for(i = 0; *(str+i) != 0; i++)
	{
		
		putc( *(str+i) );

	}

}


void putc(char byte2send)
{

	while(U1STAbits.UTXBF == 1);

	U1TXREG = byte2send;

}


char getc(void)
{

	if(U1STAbits.OERR == 1) U1STAbits.OERR = 0; // If OERR == 1 then reset OERR
	
	while(U1STAbits.URXDA == 0); // Wait while URXDA == 0

	
	if( (U1STAbits.FERR == 1) || (U1STAbits.PERR == 1) ) // If FERR or PERR then
	{

		char trash = U1RXREG; // read UxRXREG (to discard the character) 
		return 0;			  // and return 0

	}

	else // else
	{

		return U1RXREG; // Return U1RXREG

	}

}

