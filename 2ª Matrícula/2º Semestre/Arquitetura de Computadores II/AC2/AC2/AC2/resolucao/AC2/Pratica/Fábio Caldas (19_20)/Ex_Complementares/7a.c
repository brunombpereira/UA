#include <detpic32.h>

void delay(int ms);

void configPorts()
{
	//Dip-Switch
	LATB = LATB & 0xFFF0;
	TRISB = TRISB | 0x000F;
}

int main(void)
{
	configPorts();

	while(1)
	{
		int input = PORTB & 0x000F;

		printStr("RB3:");
		printInt10((input & 0x08) >> 3);
		printStr(" RB2:");
		printInt10((input & 0x04) >> 2);
		printStr(" RB1:");
		printInt10((input & 0x02) >> 1);
		printStr(" RB0:");
		printInt10((input & 0x01));
		delay(1000);
		putChar('\r');
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
