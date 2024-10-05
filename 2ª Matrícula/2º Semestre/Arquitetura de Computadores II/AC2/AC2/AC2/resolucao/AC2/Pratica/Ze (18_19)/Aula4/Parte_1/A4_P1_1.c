#include <detpic32.h>

// Functions declaration:

void delay(int);



int main(void)
{

	LATDbits.LATD0   = 0;	// Set LATD0 output 0
	TRISDbits.TRISD0 = 0;	// Set D0 as output

	while(1)
	{

		delay(500);			// half period (1Hz) -> 0.5s

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