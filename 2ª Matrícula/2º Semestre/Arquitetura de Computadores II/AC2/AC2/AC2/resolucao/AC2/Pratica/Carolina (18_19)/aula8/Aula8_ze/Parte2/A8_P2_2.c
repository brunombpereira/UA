#include <detpic32.h>

void setPWM(unsigned int);
void send2displays(unsigned char);
unsigned char toBcd(unsigned char);
void putc(char);
void configUart(unsigned int, char, unsigned int);


volatile int voltage = 0;
volatile char counter_100 = 0;
volatile int voltMin = 33;
volatile int voltMax = 0;

void _int_(24) isr_uart1(void)
{
char RX = U1RXREG;	// receive char

	if(RX == 'L')
	{

		putc('\n');
		putc( (toBcd(voltMin) >> 4)   + '0');
		putc('.');
		putc( (toBcd(voltMin) & 0x0F) + '0');
		putc('\n');
		putc( (toBcd(voltMax) >> 4)   + '0');
		putc('.');
		putc( (toBcd(voltMax) & 0x0F) + '0');
		putc('\n');
		putc('\n');

	}

	IFS0bits.U1RXIF = 0;	 // Reset UART interrupt flag
	
}

void _int_(4) isr_T1(void)
{

	AD1CON1bits.ASAM = 1;	// Start A/D conversion
	IFS0bits.T1IF = 0;	 	// Reset T1IF flag

}

void _int_(12) isr_T3(void)
{

	if(counter_100 == 99)
	{

		putc( (voltage >> 4)   + '0' );	// bcd number separation + convertion to char
		putc('.');
		putc( (voltage & 0x0F) + '0' );  
		putc('\n');

		counter_100 = 0;

	}

	send2displays(voltage);

	counter_100++;

	IFS0bits.T3IF = 0;		 // Reset timer interrupt flag

} 

void _int_(27) isr_adc(void)	// Vector number ADC1 page 75
{
	int V = 0;

	int *p = (int *)(&ADC1BUF0);
	for( ; p <= (int *)(&ADC1BUF7) ; p++)
	{

		V += *p;

	}

	V /= 8;
	V = ( ( (V*33) + 511) / 1023 );

	voltage = toBcd(V);

	if(V > voltMax) voltMax = V;
	if(V < voltMin) voltMin = V;


	IFS1bits.AD1IF = 0;		// Reset AD1IF flag

}


int main(void)
{

	int dutyCycle;

	LATDbits.LATD6 = 0;			// display high
	LATDbits.LATD5 = 0;			// display low	
	TRISD = (TRISD & 0xFF9F);
	TRISB = (TRISB & 0x00FF);	// configure RB8 to RB14 and RD5 to RD6 as outputs

	// RB4 configuration:

	TRISBbits.TRISB4 	= 1; 	// Digital -> input
	AD1PCFGbits.PCFG4  	= 0; 	// RB4 config as analog input
	AD1CON1bits.SSRC 	= 7; 	// ADC conversion config bits, mode 7
	AD1CON1bits.CLRASAM = 1; 	// conversions be4 interrupt is generated
	AD1CON3bits.SAMC    = 16;	// Sample time is 16 TAD (TAD = 100 ns)
	AD1CON2bits.SMPI	= 7;	// Interrupt is generated after x - 1 samples.
	AD1CHSbits.CH0SA	= 4;	// Desired adc input

	AD1CON1bits.ON		= 1;	// Enable adc (last command)

	// Interupt configuration:	Specific bits in the datasheet

	IPC6bits.AD1IP = 2;		// configure priority of A/D interrupts
	IFS1bits.AD1IF = 0;		// clear A/D interrupt flag
	IEC1bits.AD1IE = 1;		// enable A/D interrupts




	// Timer 3 config
	T3CONbits.TCKPS = 2; 	 // prescaler
	PR3             = 49999; // value to count up to (50000) 
	TMR3            = 0; 	 // Reset timer
	T3CONbits.ON    = 1; 	 // Enable timer

	// Timer 3 interrupt config
	IPC3bits.T3IP = 2;		 // Interrupt priority (must be in range [1..6])
	IEC0bits.T3IE = 1;		 // Enable timer interrupts
	IFS0bits.T3IF = 0;		 // Reset timer interrupt flag

	// T3 pwm config
	OC1CONbits.OCM 	  = 6;
	OC1CONbits.OCTSEL = 1;		 

	OC1CONbits.ON 	  = 1;


	// Timer 1 config
	T1CONbits.TCKPS = 4; 	 // 1/256 prescaler
	PR1             = 19530; // value to count up to (19531,25) 
	TMR1            = 0; 	 // Reset timer
	T1CONbits.ON    = 1; 	 // Enable timer


	// Timer 1 interrupt config
	IPC1bits.T1IP = 2;		 // Interrupt priority (must be in range [1..6])
	IEC0bits.T1IE = 1;		 // Enable timer interrupts
	IFS0bits.T1IF = 0;		 // Reset timer interrupt flag


	configUart(115200,'N',1);	// default "pterm" parameters
								// with RX interrupt enabled

	EnableInterrupts();


	while(1)
	{

		if( !PORTBbits.RB0 && !PORTBbits.RB1 )
		{

			IEC0bits.T1IE = 1;		 // Enable timer interrupts
			setPWM(0);

		}
		else if ( !PORTBbits.RB0 && PORTBbits.RB1 )
		{
		
			IEC0bits.T1IE = 0;		 // Disable timer interrupts
			setPWM(100);

		}
		else
		{

			IEC0bits.T1IE = 1;		 // Enable timer interrupts
			dutyCycle = voltage * 3;
			setPWM(dutyCycle);

		}

	}

	return 0;
}

void setPWM(unsigned int dutyCycle)
{

	// duty cycle 0-100

	OC1RS = (int)(dutyCycle * 499.99);

}


unsigned char toBcd(unsigned char value)
{

	return ( (value / 10 ) << 4 ) + ( value % 10 );

}



void send2displays(unsigned char value)
{

	static const char display7Scodes[16] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
					  					    0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

	static char displayFlag = 0; 	// static variable: doesn't loose its
									// value between calls to function


	if(displayFlag == 0)
	{

		LATDbits.LATD6 = 0;			// display high
		LATDbits.LATD5 = 1;			// display low	


		LATB = ( display7Scodes[(value & 0x0F)] << 8 );	// send digit_low (dl) to display_low:
																		// dl = value & 0x0F, with Dot thingie


		displayFlag = !displayFlag;

	}

	else
	{

		LATDbits.LATD6 = 1;			// display high
		LATDbits.LATD5 = 0;			// display low	

			
		LATB = ( (display7Scodes[(value >> 4)] << 8 | 0x8000 ) );	// send digit_high (dh) to display_high:
																	// dh = value >> 4. with dot.
															
		
		displayFlag = !displayFlag;

	}

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

