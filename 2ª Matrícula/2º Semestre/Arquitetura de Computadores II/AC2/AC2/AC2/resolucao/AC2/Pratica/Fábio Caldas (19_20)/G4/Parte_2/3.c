#include <detpic32.h>
void delay(int ms);
void send2displays(unsigned char value);

void configPort()
{
	LATB = LATB & 0x80FF;
	TRISB = TRISB & 0x80FF;

	LATD = LATD & 0xFF9F;
	TRISD = TRISD & 0xFF9F;
}

int main(void)
{
	configPort();
	
	int counter = 0;
	unsigned int i = 0;

	while(1)
	{
		i++;
		send2displays(counter);
		delay(50);
		if(i % 4 == 0)
			counter++;
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

	unsigned char dl = value & 0x0F;	//isolar os 4 lsb
	unsigned char dh = value >> 4;		//isolar os 4 msb

	if(displayFlag == 0)
	{
		//Enable Display_low
		LATDbits.LATD5 = 1;
		LATDbits.LATD6 = 0;

		LATB = display7Scodes[dl] << 8;	//Envia para o displays_low os 8 bits menos
							  			//significativos do "value"
		delay(100);
	} else
	{
		//Enable Display_high
		LATDbits.LATD5 = 0;
		LATDbits.LATD6 = 1;

		LATB = display7Scodes[dh] << 8;	//Envia para o displays_high os 8 bits menos
							  			//significativos do "value"
		delay(100);
	}
	displayFlag = !displayFlag;
}
