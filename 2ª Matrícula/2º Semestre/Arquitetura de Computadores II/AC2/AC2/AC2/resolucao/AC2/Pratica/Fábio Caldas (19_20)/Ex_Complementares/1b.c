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
		LATEbits.LATE0 = PORTBbits.RB3;
		LATEbits.LATE1 = PORTBbits.RB2;
		LATEbits.LATE2 = PORTBbits.RB1;
		LATEbits.LATE3 = PORTBbits.RB0;
	}
	return 0;
}
