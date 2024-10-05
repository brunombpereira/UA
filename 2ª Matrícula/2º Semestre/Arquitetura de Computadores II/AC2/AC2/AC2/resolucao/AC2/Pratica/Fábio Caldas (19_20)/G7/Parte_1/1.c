#include <detpic32.h>

void configPortos()
{

}

void configT3()
{
	T3CONbits.TCKPS = 7;	//K_Prescaler
	PR3 = 39062;			//Prescaler
	TMR3 = 0;				//Reset T3 count register
	T3CONbits.TON = 1;		//Enable timer T3

	//T3 interrupt config
	IPC3bits.T3IP = 2;		//interrupt priority
	IEC0bits.T3IE = 0;		//Enable timer T3 interrupts
	IFS0bits.T3IF = 0;		//Reset T3 interrupt flag
}

int main(void)
{
	configPortos();
	configT3();

	while(1)
	{
		while(IFS0bits.T3IF == 0);
		IFS0bits.T3IF = 0;
		putChar('.');
	}
	return 0;
}
