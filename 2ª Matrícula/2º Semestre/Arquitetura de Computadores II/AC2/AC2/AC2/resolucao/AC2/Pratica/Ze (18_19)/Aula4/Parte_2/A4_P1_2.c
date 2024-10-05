#include <detpic32.h>

void send2displays(unsigned char);
void delay(int);
void BinCounter();

int main()
{

	LATDbits.LATD6 = 0;			// display high
	LATDbits.LATD5 = 0;			// display low	
	TRISB = (TRISB & 0x00FF);	// configure RB8 to RB14 and RD5 to RD6 as outputs
	TRISD = (TRISD & 0xFF9F);
	
	BinCounter();

	return 0;

}


void BinCounter()
{

	unsigned char i;

	for(i = 0 ;   ; i++)
	{

		send2displays(i);
		delay(200);

	}

}


void send2displays(unsigned char value)
{

	static const char display7Scodes[16] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
					  					    0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};


	LATDbits.LATD6 = 1;			// display high
	LATDbits.LATD5 = 0;			// display low	
	LATB = ( display7Scodes[(value >> 4)] << 8 );	// send digit_high (dh) to display_high: dh = value >> 4
	


	LATDbits.LATD6 = 0;			// display high
	LATDbits.LATD5 = 1;			// display low	
	LATB = ( display7Scodes[(value & 0x0F)] << 8 );	// send digit_low (dl) to display_low: dl = value & 0x0F

}


void delay(int ms)
{
	
	for(; ms > 0; ms--)
		
		{	
			resetCoreTimer();
			while(readCoreTimer() < 20000);
		}

}

