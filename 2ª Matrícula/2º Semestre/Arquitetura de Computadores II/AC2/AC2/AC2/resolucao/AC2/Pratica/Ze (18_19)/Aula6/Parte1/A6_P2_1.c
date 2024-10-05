#include <detpic32.h>

void send2displays(unsigned char);
void delay(int);
unsigned char toBcd(unsigned char);

volatile unsigned char voltage = 0;	// Global variable

// Interrupt Handler
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

	

	IFS1bits.AD1IF = 0;		// Reset AD1IF flag

}



int main(void)
{

	unsigned int cnt = 0;

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

	EnableInterrupts();

	AD1CON1bits.ASAM = 1;	// Start conversion

	while(1)
	{

		if(cnt % 25 == 0)	// 250 ms (4 S/s)
		{
			AD1CON1bits.ASAM = 1;	// Start conversion
		}

		send2displays(voltage);

		cnt++;

		delay(10);

	}

	return 0;

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


void delay(int ms)
{
	
	for(; ms > 0; ms--)
		
		{	
			resetCoreTimer();
			while(readCoreTimer() < 20000);
		}

}

