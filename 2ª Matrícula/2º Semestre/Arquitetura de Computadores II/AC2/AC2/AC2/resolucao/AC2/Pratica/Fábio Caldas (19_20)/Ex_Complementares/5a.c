#include <detpic32.h>

void delay(int ms);
void send2display(unsigned char value);

void configPortos()
{

}

int main(void)
{
	configPortos();

	int counter100 = 0;

	while(1)
	{
		counter100 = (counter100 + 1) % 100;
		printInt(counter100, 10 | 2 << 16);
		printStr("\r");
		delay(100);
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

void send2display(unsigned char value)
{
	static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
	
	unsigned char dl = value & 0x0F;
	unsigned char dh = value >> 4;

	static char dispFlag = 0;

	if(dispFlag == 0)
	{
		LATDbits.LATD5 = 1;
		LATDbits.LATD6 = 0;

		LATB = display7Scodes[dl] << 8;
	} else
	{
		LATDbits.LATD5 = 0;
		LATDbits.LATD6 = 1;

		LATB = display7Scodes[dh] << 8;
	} dispFlag = !dispFlag;
}
