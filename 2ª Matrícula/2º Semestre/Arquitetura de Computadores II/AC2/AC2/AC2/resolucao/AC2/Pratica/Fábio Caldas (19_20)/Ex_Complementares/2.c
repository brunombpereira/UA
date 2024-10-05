#include <detpic32.h>

void delay(int ms);

void configPorts()
{
	LATE = LATE & 0xFFF0;
	TRISE = TRISE & 0xFFF0;
}

int main(void)
{
	configPorts();

	char input;

	while(1)
	{
		input = getChar();

		switch(input)
		{
			case '0':
				LATEbits.LATE0 = 1;
				break;

			case '1':
				LATEbits.LATE1 = 1;
				break;

			case '2':
				LATEbits.LATE2 = 1;
				break;

			case '3':
				LATEbits.LATE3 = 1;
				break;

			default:
				LATE = LATE | 0x000F;
				delay(1000);
				LATE = LATE & 0xFFF0;
				break;
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
