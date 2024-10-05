#include <detpic32.h>

void delay(int ms);

void configPortos()
{
	
}

int main(void)
{
	configPortos();

	int counter100 = 0;
	int freq = 10;
	int input;

	while(1)
	{
		input = inkey();
		printInt(counter100, 10 | 2 << 16);

		if(input >= '0' && input <= '4')
		{
			freq = 10*(1+(input - '0'));
		}
		else if(input == '\n')
		{
			printStr(" >> ");
			printInt(counter100, 10 | 2 << 16);
		}

		putChar('\r');
		counter100 = (counter100 + 1) % 100;
		delay(1000/freq);
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
