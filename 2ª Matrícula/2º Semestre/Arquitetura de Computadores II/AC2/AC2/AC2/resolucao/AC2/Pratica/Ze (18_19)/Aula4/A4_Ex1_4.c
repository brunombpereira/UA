#include <detpic32.h>

int main(void)
{

	PORTDbits.RD0 = 1;
	TRISDbits.TRISD0 = 0; // output

	PORTDbits.RD0 = 0;
	PORTDbits.RD0 = !PORTDbits.RD0;

	return 0;
}


/*

#include <detpic32.h>

int main(void)
{

	PORTDbits.RD0 = 1;
	TRISDbits.TRISD0 = 0; // output

	PORTDbits.RD0 = 0; 
	asm volatile("nop"); //inline assembly
	asm volatile("nop");
	PORTDbits.RD0 = !PORTDbits.RD0;

	return 0;
}

*/


