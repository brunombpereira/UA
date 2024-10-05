#include <detpic32.h>

int main(void)
{

	// Timer 3 config
	T3CONbits.TCKPS = 2; 	 // prescaler
	PR3             = 49999; // value to count up to (50000) 
	TMR3            = 0; 	 // Reset timer
	T3CONbits.ON    = 1; 	 // Enable timer


	OC1CONbits.OCM 	  = 6;
	OC1CONbits.OCTSEL = 1;		 
	OC1RS 			  = 12500;
	OC1CONbits.ON 	  = 1;

	while(1);

	return 0;
}
