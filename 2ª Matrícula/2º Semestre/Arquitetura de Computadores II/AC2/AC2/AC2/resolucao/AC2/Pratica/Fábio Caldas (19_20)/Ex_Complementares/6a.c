#include <detpic32.h>

void configPortos()
{
	
}

void configT3()
{
	T3CONbits.TCKPS = 5;		//K_prescaler == 32 => K = 5
	PR3 = 62499;
	TMR3 = 0;
	T3CONbits.TON = 1;

	IPC3bits.T3IP = 2;
	IEC0bits.T3IE = 1;
	IFS0bits.T3IF = 0;
}

volatile unsigned int counter100 = 0;

int main(void)
{
	configPortos();
	configT3();

	EnableInterrupts();

	while(1)
	{
		
	}

	return 0;
}

void _int_(12) isr_T3(void)
{
	int input = inkey();
	printInt(counter100, 10 | 2 << 16);

	if(input >= '0' && input <= '4')
	{
		PR3 = ((20000000/32)/(10*(1+(input-'0'))))-1;
	}
	else if(input == '\n')
	{
		printStr(">>");
		printInt(counter100, 10 | 2 << 16);
	}

	putChar('\r');
	counter100 = (counter100 + 1) % 100;

	IFS0bits.T3IF = 0;
}
