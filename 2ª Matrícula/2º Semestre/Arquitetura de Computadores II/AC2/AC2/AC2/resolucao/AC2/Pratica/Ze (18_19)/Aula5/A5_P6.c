#include <detpic32.h>

unsigned char averageCH4();
void send2displays(unsigned char);
void delay(int);
unsigned char toBcd(unsigned char);

int main(void)
{

	LATDbits.LATD6 = 0;			// display high
	LATDbits.LATD5 = 0;			// display low	
	TRISD = (TRISD & 0xFF9F);
	TRISB = (TRISB & 0x00FF);	// configure RB8 to RB14 and RD5 to RD6 as outputs



	LATEbits.LATE0 = 0;	// Set digital output = 0.
	TRISEbits.TRISE0 = 0;	// Digital output for time measurement



	// RB4 configuration:

	TRISBbits.TRISB4 	= 1; 	// Digital -> input
	AD1PCFGbits.PCFG4  	= 0; 	// RB4 config as analog input
	AD1CON1bits.SSRC 	= 7; 	// ADC conversion config bits, mode 7
	AD1CON1bits.CLRASAM = 1; 	// conversions be4 interrupt is generated
	AD1CON3bits.SAMC    = 16;	// Sample time is 16 TAD (TAD = 100 ns)
	AD1CON2bits.SMPI	= 3;	// Interrupt is generated after x - 1 samples.
	AD1CHSbits.CH0SA	= 4;	// Desired adc input

	AD1CON1bits.ON		= 1;	// Enable adc (last command)

	unsigned char i = 0, voltage = 0;

	while(1)
	{

		LATEbits.LATE0 = 1;				// Time measurement bit

		AD1CON1bits.ASAM = 1;			// Start conversion

		while( IFS1bits.AD1IF == 0 );	// Wait while conversion not done

		LATEbits.LATE0 = 0;				// Time measurement bit

		if(i++ % 25 == 0)
		{

			voltage = toBcd(averageCH4());

		}
		
		send2displays(voltage);

		delay(10);

		IFS1bits.AD1IF = 0;	// Reset


		if(i == 200) 	i = 0;		// Reset i cuz 8 bit = 255 (when it autoresets 100 + 55)
	}

	return 0;

}



unsigned char averageCH4()	// with rounding
{

	int sum = 0; // Usado para a média

	// Valores convertidos para tensão COM arredondamento:

	int *p = (int *)(&ADC1BUF0);
	for(; p <= (int *)(&ADC1BUFF); p += 4 )
	{

		sum += *p;	// Usado para a média
		
	}

	
	return (unsigned char)(( ( sum / 4 ) * 33 + 511) / 1023) ; // returns rounded average voltage

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


