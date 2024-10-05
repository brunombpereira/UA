#include <detpic32.h>
void delay(int ms);
void send2displays(unsigned char value);
unsigned char toBcd(unsigned char value);

void configPort()
{
	LATB = LATB & 0x80FF;
	TRISB = TRISB & 0x80FF;

	LATD = LATD & 0xFF9F;
	TRISD = TRISD & 0xFF9F;

	LATBbits.LATB15 = 0;
	TRISBbits.TRISB15 = 0;
}

int main(void)
{
	configPort();
	
	int counter = 0;
	unsigned int i = 0;

	while(1)
	{
		i++;
		send2displays(toBcd(counter));
		delay(10);
		if(i % 100 == 0)
			counter++;
			counter = counter % 60;
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

void send2displays(unsigned char value)
{
	static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
	static char displayFlag = 0;

	unsigned char dl = value & 0x0F;
	unsigned char dh = value >> 4;

	if(displayFlag == 0)
	{
		LATDbits.LATD5 = 1;
		LATDbits.LATD6 = 0;

		LATB = display7Scodes[dl] << 8;

		if(value % 2 == 0)
			LATBbits.LATB15 = 1;
		else
			LATBbits.LATB15 = 0;

	} else
	{
		LATDbits.LATD5 = 0;
		LATDbits.LATD6 = 1;

		LATB = display7Scodes[dh] << 8;

		if(value % 2 == 0)
			LATBbits.LATB15 = 1;
		else
			LATBbits.LATB15 = 0;

	}
	displayFlag = !displayFlag;
}

unsigned char toBcd(unsigned char value)
{
	
	return ((value /10) << 4) + (value % 10);
}
