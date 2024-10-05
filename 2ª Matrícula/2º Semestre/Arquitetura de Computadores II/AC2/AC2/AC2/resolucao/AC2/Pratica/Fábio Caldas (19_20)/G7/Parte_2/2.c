#include <detpic32.h>

void configT3() //100Hz
{
	T3CONbits.TCKPS = 2;
	PR3 = 49999;
	TMR3 = 0;
	T3CONbits.TON = 1;
}

void configOC1() //25% dutyCycle
{
	OC1CONbits.OCM = 6;		// PWM mode on OC1
	OC1CONbits.OCTSEL = 1;	// 0 = T2; 1 = T3;
	OC1CONbits.ON = 1;
}

void setPWM(unsigned int dutyCycle)
{
	if(dutyCycle >= 0 && dutyCycle <= 100)
		OC1RS = ((PR3+1)*dutyCycle)/100;
}

int main(void)
{
	configT3();
	configOC1();
	setPWM(25);

	TRISBbits.TRISB5 = 1;
	int Ton;

	while(1)
	{
		while(PORTBbits.RB5 == 1);
		while(PORTBbits.RB5 == 0);
		resetCoreTimer();
		while(PORTBbits.RB5 == 1);
		Ton=readCoreTimer()/20;
		printInt(Ton,10);
		printStr(" micros");
		putChar('\n');
	}

	return 0;
}
