#include <detpic32.h>

void delay(int ms);
void send2displays(unsigned char value);

void configPorts()
{
	LATE = LATE & 0xFFF0;
	TRISE = TRISE & 0xFFF0;

	LATB = LATB & 0x00FF;
	TRISB = TRISB & 0x00FF;

	LATD = LATD & 0xFF9F;
	TRISD = TRISD & 0xFF9F;
}

int main(void)
{
	configPorts();

	char input;
	char toDisplay = 0;

	while(1)
	{
		int counter = 0;
		input = inkey();

		if(input != 0)
		{
			TRISD = TRISD & 0xFF9F;
			if(input == '0')
			{
				LATEbits.LATE0 = 1;
				toDisplay = 0;
			}
			else if(input == '1')
			{
				LATEbits.LATE1 = 1;
				toDisplay = 1;
			}
			else if(input == '2')
			{
				LATEbits.LATE2 = 1;
				toDisplay = 2;
			}
			else if(input == '3')
			{
				LATEbits.LATE3 = 1;
				toDisplay = 3;
			}
			else
			{
				do
				{
					send2displays(0xFF);
					LATE = LATE | 0x000F;
					delay(10);
				}while(++counter <= 100);
				LATE = LATE & 0xFFF0;
				//LATD = LATD & 0xFF9F;
				TRISD = TRISD | 0x0060;
				toDisplay = 0; 
			}
		}
		send2displays(toDisplay);
		delay(10);
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
		} else
		{
			LATDbits.LATD5 = 0;
			LATDbits.LATD6 = 1;

			LATB = display7Scodes[dh] << 8;
		}
		displayFlag = !displayFlag;
}
