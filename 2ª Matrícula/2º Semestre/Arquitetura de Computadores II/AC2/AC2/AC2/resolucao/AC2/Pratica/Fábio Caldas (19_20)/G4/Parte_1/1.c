#include <detpic32.h>
void delay(int ms);

void configPorts()
{
	LATDbits.LATD0 = 0;		//D0 = 0
	TRISDbits.TRISD0 = 0;	//D0 Output
}

int main(void)
{
	configPorts();

	while(1)
	{
		delay(500);			//half period = 0.5s
		LATDbits.LATD0 = !LATDbits.LATD0;
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
