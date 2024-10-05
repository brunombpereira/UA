#include <detpic32.h>

void delay(int ms);

void configPort()
{
	LATB = LATB & 0x80FF;	//RB8-14 = 0
	TRISB = TRISB & 0x80FF;	//RB8-14 Outputs (Disp7Seg)

	TRISD = TRISD & 0xFF9F; //RD5-6 Outputs
	LATDbits.LATD5 = 0; 	//display_low, on;
	LATDbits.LATD6 = 1;		//display_high, off;
}

int main(void)
{
	configPort();
	
	unsigned char segment;	//UChar/Char = 8 bits
	int i;					//UInt/int = 16 bits (w/ 8msb = 0)

	while(1)
	{
		//Toggle display selection
		LATDbits.LATD5 = !LATDbits.LATD5;
		LATDbits.LATD6 = !LATDbits.LATD6;
		//segment = 1
		segment = 0x0008;
		for(i = 0; i < 7; i++)
		{
			//LATB = segment << 8; //Send "segment" value to display
			LATB = (LATB & 0x80FF) | segment;
			segment = segment << 1;
			delay(500);
		}
	}

	return 0;
}

void delay(int ms)
{
	for(; ms > 0; ms--)
	{
		resetCoreTimer();
		while(readCoreTimer() < 20000);
	}
}
