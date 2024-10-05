#include <detpic32.h>

#define SAMPLES 1

void delay(int ms);

void configPorts()
{
	//Dip-Switch
	LATB = LATB & 0xFFF0;
	TRISB = TRISB | 0x000F;
}

void configADC()
{
	TRISBbits.TRISB4 = 1;
	AD1PCFGbits.PCFG4 = 0;
	AD1CON1bits.SSRC = 7;
	AD1CON1bits.CLRASAM = 1;
	AD1CON3bits.SAMC = 16;
	AD1CON2bits.SMPI = SAMPLES - 1;
	AD1CHSbits.CH0SA = 4;
	AD1CON1bits.ON = 1;
}

int main(void)
{
	configPorts();
	configADC();

	int input, VALadc, freq, T;

	while(1)
	{
		AD1CON1bits.ASAM = 1;
		while(IFS1bits.AD1IF == 0);
		VALadc = ADC1BUF0;
		IFS1bits.AD1IF = 0;

		freq = 1+(VALadc/255);
		T = 1000/freq;					//1000/freq pq queremos ms e n s

		input = PORTB & 0x000F;

		printStr("RB3:");
		printInt10((input & 0x08) >> 3);
		printStr(" RB2:");
		printInt10((input & 0x04) >> 2);
		printStr(" RB1:");
		printInt10((input & 0x02) >> 1);
		printStr(" RB0:");
		printInt10((input & 0x01));
		
		/*	DEBUG
		printStr("\tf: ");
		printInt10(freq);
		printStr("Hz");
		printStr(" T: ");
		printInt10(T);
		printStr("ms");
		*/

		delay(T);
		putChar('\r');
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
