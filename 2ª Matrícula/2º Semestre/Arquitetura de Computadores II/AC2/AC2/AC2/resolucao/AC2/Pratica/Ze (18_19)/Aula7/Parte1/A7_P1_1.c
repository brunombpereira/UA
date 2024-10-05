#include <detpic32.h>

int main(void)
{

	T3CONbits.TCKPS = 7; 	 // 1/256 prescaler
	PR3             = 39061; // value to count up to (39062,5) 
	TMR3            = 3; 	 // Reset timer
	T3CONbits.ON    = 1; 	 // Enable timer


	while(1)
	{

		while(IFS0bits.T3IF != 1);
		IFS0bits.T3IF = 0;

		putChar('.');

	}


	return 0;
}
