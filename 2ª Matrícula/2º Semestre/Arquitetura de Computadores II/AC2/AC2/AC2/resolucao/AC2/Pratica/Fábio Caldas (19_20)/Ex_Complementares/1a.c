#include <detpic32.h>

void configPorts()
{
	//RB0-3 Inputs
	LATB = LATB & 0xFFF0;
	TRISB = TRISB | 0x000F;

	//RE0-3 Outputs
	LATE = LATE & 0xFFF0;
	TRISE = TRISE & 0xFFF0;
}

int main(void)
{
	configPorts();
	int input;

	while(1)
	{
		LATE = PORTB;
	}

	return 0;
}
