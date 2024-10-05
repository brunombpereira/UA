#include<detpic32.h>

#define DisableUart1RxInterrupt()	IEC0bits.U1RXIE = 0;
#define EnableUart1RxInterrupt()	IEC0bits.U1RXIE = 1;

#define DisableUart1TxInterrupt()	IEC0bits.U1TXIE = 0;
#define EnableUart1TxInterrupt()	IEC0bits.U1TXIE = 1;

#define BUF_SIZE 8
#define INDEX_MASK (BUF_SIZE - 1)

void comDrv_config(unsigned int, char, unsigned int);

typedef struct
{

	unsigned char data[BUF_SIZE];
	unsigned int head;
	unsigned int tail;
	unsigned int count;

} circularBuffer;

volatile circularBuffer txb;	// Transmission buffer
volatile circularBuffer rxb;	// Reception buffer

void comDrv_flushRx(void)
{

	// Initialize variables of the reception buffer

	rxb.head  = 0;
	rxb.tail  = 0;
	rxb.count = 0;

}

void comDrv_flushTx(void)
{

	// Initialize variables of the transmission buffer

	txb.head  = 0;
	txb.tail  = 0;
	txb.count = 0;

}

void comDrv_putc(char ch)
{

	while(txb.count == BUF_SIZE); // Wait while buffer is full
	txb.data[txb.tail] = ch;	  // Copy character to the transmission
								  // buffer at position "tail"

	txb.tail = (txb.tail + 1) & INDEX_MASK; // Increment "tail" index
											// (mod BUFF_SIZE)

	DisableUart1TxInterrupt();	  // Begin of critical section

	txb.count++;

	EnableUart1TxInterrupt();

}

void comDrv_puts(char *s)
{

	for( ; *s != '\0' ; s++)
	{

		comDrv_putc( *s );

	}

}

char comDrv_getc(char *pchar)
{

	if(rxb.count == 0)	// Test "count" variable (reception buffer) and return FALSE
		return 0;   	// if it is zero

	DisableUart1RxInterrupt();   // Begin of critical section
	
	*pchar = rxb.data[rxb.head]; // Copy character pointed by "head" to *pchar
	rxb.count--;				 // Decrement "count" variable
	rxb.head = (rxb.head + 1) & INDEX_MASK; // Increment "head" variable (mod BUF_SIZE)
	
	EnableUart1RxInterrupt(); 	 // End of critical section
	
	return 1; // Return true

}

void _int_(24) isr_uart1(void)
{

	if(IFS0bits.U1TXIF) // if U1TXIF is set
	{
		
		if(txb.count > 0)// if "count" variable (transmission buffer, txb) is greater than 0
		{
		
			U1TXREG = txb.data[txb.head]; // Copy character pointed by "head" to U1TXREG register
			txb.head = (txb.head + 1) & INDEX_MASK;	// Increment "head" variable (mod BUF_SIZE)
			txb.count--;		// Decrement "count" variable
		
		}
	
		if(txb.count == 0)	 // if "count" variable is 0 then
			DisableUart1TxInterrupt();
	
		IFS0bits.U1TXIF = 0; // Reset UART1 TX interrupt flag
	}


	if(IFS0bits.U1RXIF)
	{
		rxb.data[rxb.tail] = U1RXREG;	// Read character from UART and
										// write it to the "tail" position
										// of the reception buffer

		rxb.tail = (rxb.tail + 1) & INDEX_MASK;	// Increment "tail" variable (mod BUF_SIZE)
		if(rxb.count < BUF_SIZE) // If reception buffer is not full 
								 // (e.g. count < BUFF_SIZE) then
			rxb.count++; // increment "count" variable
	
		else // Else
		
			rxb.head++;	// increment "head" variable (discard oldest character)
		
			
		IFS0bits.U1RXIF = 0; // reset UART1 RX interrupt flag		

	}


}

int main(void)
{
	
	unsigned char charRX = 0;

	comDrv_config(115200,'N',1); 	// default "pterm" parameters
									// with TX and RX interrupts disabled
	
	comDrv_flushRx();
	comDrv_flushTx();
	
	EnableInterrupts();

	comDrv_puts("PIC32 UART Device-driver\n");

	while(1)
	{
		
		while( comDrv_getc( &charRX ) == 0 );
		
		if(charRX == 'S')
			comDrv_puts("\n\nbatatas, patatas, pomme de terre, kartofell, kartofi, kartoshki, shu tiao\n\n");

		else
			comDrv_putc( charRX );

	}
	return 0;

}


void comDrv_config(unsigned int baud, char parity, unsigned int stopbits)
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

	// RX
	IEC0bits.U1RXIE = 1;	 // Enable UART Rx interrupts
	IFS0bits.U1RXIF = 0;	 // Reset UART interrupt flag

	// TX
	IEC0bits.U1TXIE = 0;	 // Disable UART interrupts
	IFS0bits.U1TXIF = 0;	 // Reset UART IF.

}

