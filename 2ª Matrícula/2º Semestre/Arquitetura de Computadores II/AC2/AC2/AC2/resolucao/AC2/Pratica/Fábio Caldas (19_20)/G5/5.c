#include <detpic32.h>
#define SAMPLES 4
void delay(int ms);
void send2displays(unsigned char value);
unsigned char toBcd(unsigned char value);

void configPorts()
{
	LATB = LATB & 0x80FF;
	TRISB = TRISB & 0x80FF;

	LATD = LATD & 0xFF9F;
	TRISD = TRISD & 0xFF9F;
}

void configADC()
{
	TRISBbits.TRISB4 = 1;			//RB4 digital output disconnected
	AD1PCFGbits.PCFG4 = 0;			//RB4 configured as analog input (AN4)
	AD1CON1bits.SSRC = 7;			//Conversion trigger selection(bits)
	AD1CON1bits.CLRASAM = 1;		//Stop conversion when 1st A/D converter interrupt is generated. Clear ASAM bit
	AD1CON3bits.SAMC = 16;			//Sample time
	AD1CON2bits.SMPI = SAMPLES-1;	//Interrupt generated after SAMPLES samples
	AD1CHSbits.CH0SA = 4;			//Selection of the analog input(AN4) for conversion
	AD1CON1bits.ON = 1;				//Enable A/D converter
}

int main(void)
{
	configPorts();
	configADC();
	
	int i = 0;

	while(1)
	{
		int sum = 0;
		int average, voltage, voltage10;

		if(i++ % 25 == 0)
		{
			AD1CON1bits.ASAM = 1;		//start conversion
			while(IFS1bits.AD1IF == 0); //Polling
			int *p = (int *)(&ADC1BUF0);
			for(; p <= (int *)(&ADC1BUFF); p+=4)
			{
				//printInt(*p, 10 | 4 << 10);
				//printStr(" ");
				sum += *p;
			}
			average = sum/SAMPLES;
			voltage = (average*33)/1023;
			voltage10 = toBcd(voltage);
			//printStr("\nAverage voltage: ");
			//printInt10(voltage);
			//printStr("\n\n");

			IFS1bits.AD1IF = 0;			//reset A/D interrupt flag (conversion finished)
		}
		send2displays(voltage10);
		delay(10);
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

unsigned char toBcd(unsigned char value)
{
	
	return ((value /10) << 4) + (value % 10);
}
