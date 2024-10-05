#include <detpic32.h>

void send2displays(unsigned char);
void delay(int);
unsigned char toBcd(unsigned char);


int main(void)
{

	LATDbits.LATD6 = 0;			// display high
	LATDbits.LATD5 = 0;			// display low	
	TRISB = (TRISB & 0x00FF);	// configure RB8 to RB14 and RD5 to RD6 as outputs
	
	TRISD = (TRISD & 0xFF9F);



	unsigned char counter = 0, i = 0;

	while(1)
	{

		i++;

		send2displays( toBcd(counter) );

		delay(10); // 100 Hz

		if(i % 100 == 0) counter++;
			// increment counter

		if(i == 200) 		i = 0;			// Reset i cuz 8 bit = 255 (when it autoresets 100 + 55)
		if(counter == 100)	counter = 0;	// Counts till 99 (+1 cuz sends on next cycle)

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
		LATB = ( display7Scodes[(value & 0x0F)] << 8 );	// send digit_low (dl) to display_low: dl = value & 0x0F
	
		displayFlag = !displayFlag;

	}

	else
	{

		LATDbits.LATD6 = 1;			// display high
		LATDbits.LATD5 = 0;			// display low	
		LATB = ( display7Scodes[(value >> 4)] << 8 );	// send digit_high (dh) to display_high: dh = value >> 4
		
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

