#include <detpic32.h>

int main(void)
{

	// RB4 configuration:

	TRISBbits.TRISB4 	= 1; 	// Digital -> input
	AD1PCFGbits.PCFG4  	= 0; 	// RB4 config as analog input
	AD1CON1bits.SSRC 	= 7; 	// ADC conversion config bits, mode 7
	AD1CON1bits.CLRASAM = 1; 	// conversions be4 interrupt is generated
	AD1CON3bits.SAMC    = 16;	// Sample time is 16 TAD (TAD = 100 ns)
	AD1CON2bits.SMPI	= 0;	// Interrupt is generated after x - 1 samples.
	AD1CHSbits.CH0SA	= 4;	// Desired adc input

	AD1CON1bits.ON		= 1;	// Enable adc (last command)

	while(1)
	{

		AD1CON1bits.ASAM = 1;			// Start conversion

		while( IFS1bits.AD1IF == 0 );	// Wait while conversion not done


		int *p = (int *)(&ADC1BUF0);
		for(; p <= (int *)(&ADC1BUFF); p += 4 )
		{

			printInt( *p, 10 + (4 << 16) ); // Print Buffer 4*4 Bytes (Byte addressable thingy) 0x10
											// (..., 16 + 16 bits) 16 msb, nr of digits, + base

			if( (int)p % 4 == 0 )	putChar(' ');
		
		}

		putChar('\n');

		IFS1bits.AD1IF = 0;	// Reset

	}

	return 0;

}

