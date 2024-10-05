#include <detpic32.h>

void delay(int ms);
void send2displays(unsigned char value);
unsigned char toBcd(unsigned char value);

void configPorts()
{
	LATB = LATB & 0x80FF;
	TRISB = TRISB & 0x80FF;

	LATD = LATD & 0xFF9F;
	TRISD = TRISD & 0xFF9F;
}

int main(void)
{
	configPorts();

	unsigned char counter = 0;
	unsigned char piscaCounter = 0;
	unsigned char resetCounter = 0;
	unsigned char i, j;

	while(1)
	{
		i = 0;
		if(resetCounter == 0)
		{
			do
			{
				send2displays(toBcd(counter));
				delay(10); //100Hz
			} while(++i < 100);
			counter++;
			counter = counter % 60;
			if(counter % 60 == 0)
			{
				counter = 0;
				resetCounter = 1;
			}
		} else
		{
			do
			{
				do
				{
					send2displays(toBcd(counter));
					delay(10);
				} while(++j < 50);
				piscaCounter++;
				j = 0;
				do
				{
					LATB = LATB & 0x00ff;
					delay(10);
				} while(++j < 50);
				piscaCounter++;
				j = 0;
			} while(piscaCounter <= 10);
			resetCounter = 0;
			counter++;
		}
		
	}

	return 0;
}

//Refresh rate 100Hz(10ms); Increment rate 1Hz(1000ms-> 1000/10) (counter =% 60)

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
	static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
										  0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
	static char displayFlag = 0;

	//Como queremos mandar 1 byte = 8 bits = 1 char
	int digit_low = value & 0x0f;	//isolar os 4 bits -significativos
	int digit_high = value >> 4;	//isolar os 4 bits +significativos
	
	if(displayFlag == 0)
	{
		//Activate Display_low
		LATDbits.LATD5 = 1;
		LATDbits.LATD6 = 0;

		LATB = display7Scodes[dl] << 8;

		if(value % 2 == 0)
			LATBbits.LATB15 = 1;

	} else
	{
		//Activate Display_high
		LATDbits.LATD5 = 0;
		LATDbits.LATD6 = 1;

		LATB = display7Scodes[dh] << 8;
		
		if(value % 2 == 0)
			LATBbits.LATB15 = 1;
		
	} displayFlag = !displayFlag;
}

unsigned char toBcd(unsigned char value)
{
	
	return ((value / 10) << 4) + (value % 10);
}
