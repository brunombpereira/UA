#include <detpic32.h>

void delay(int ms);
void send2displays(unsigned char value);
char toBcd(unsigned char value);

void configPortos()
{
	LATB = LATB & 0x00FF;
	TRISB = TRISB & 0x00FF;

	LATD = LATD & 0xFF9F;
	TRISD = TRISD & 0xFF9F;
}

void configT2()	// 50Hz
{
	T2CONbits.TCKPS = 3;		//K_prescaler == 7 => K = 3
	PR2 = 49999;
	TMR2 = 0;
	T2CONbits.TON = 1;

	IPC2bits.T2IP = 3;
	IEC0bits.T2IE = 1;
	IFS0bits.T2IF = 0;
}

void configT3() // Freq programada (10 < x < 40)
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
volatile unsigned int toDisplay;

int main(void)
{
	configPortos();
	configT2();
	configT3();

	EnableInterrupts();

	while(1){}

	return 0;
}

void _int_(8) isr_T2(void)
{
	send2displays(toDisplay);

	IFS0bits.T2IF = 0;
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
		printStr(" >> ");
		printInt(counter100, 10 | 2 << 16);
		toDisplay = toBcd(counter100);
	}

	putChar('\r');
	counter100 = (counter100 + 1) % 100;

	IFS0bits.T3IF = 0;
}

void delay(int ms)
{
	for(; ms > 0; ms--)
	{
		resetCoreTimer();
		while(readCoreTimer() < 20000);
	}
}

void send2displays(unsigned char value)
{
	static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
	static char displayFlag = 0;

	unsigned char dl = value & 0x0F;
	unsigned char dh = value >> 4;

	if(displayFlag == 0)
	{
		LATDbits.LATD5 = 1;
		LATDbits.LATD6 = 0;

		LATB = display7Scodes[dl] << 8;
	} else
	{
		LATDbits.LATD5 = 0;
		LATDbits.LATD6 = 1;

		LATB = display7Scodes[dh] << 8;
	}
	displayFlag = !displayFlag;
}

char toBcd(unsigned char value)
{
	
	return ((value/10) << 4) + (value % 10);
}
