#include <detpic32.h>

volatile unsigned char flag = 0;

void _int_(12) isr_T3(void)
{

	flag = !flag;

	if(flag)
	{
		putChar('.');
	}

	IFS0bits.T3IF = 0;

} 

int main(void)
{

	// Timer config
	T3CONbits.TCKPS = 7; 	 // 1/256 prescaler
	PR3             = 39061; // value to count up to (39062,5) 
	TMR3            = 3; 	 // Reset timer
	T3CONbits.ON    = 1; 	 // Enable timer


	// Timer interrupt config
	IPC3bits.T3IP = 2;		 // Interrupt priority (must be in range [1..6])
	IEC0bits.T3IE = 1;		 // Enable timer T2 interrupts
	IFS0bits.T3IF = 0;		 // Reset timer T2 interrupt flag

	EnableInterrupts();


	while(1);

	return 0;
}
