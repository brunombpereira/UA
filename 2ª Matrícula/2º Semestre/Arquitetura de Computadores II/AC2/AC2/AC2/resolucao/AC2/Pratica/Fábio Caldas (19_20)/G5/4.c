#include <detpic32.h>
#define SAMPLES 4
void delay(int ms);

void configPorts()
{

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

	while(1)
	{
		int sum = 0;
		int average, voltage;
		int *p = (int *)(&ADC1BUF0);

		AD1CON1bits.ASAM = 1;		//start conversion
		while(IFS1bits.AD1IF == 0); //Polling
		for(; p <= (int *)(&ADC1BUFF); p+=4)
		{
			printInt(*p, 10 | 4 << 10);
			printStr(" ");
			sum += *p;
		}
		average = sum/SAMPLES;
		voltage = (average*33)/1023;
		printStr("\nAverage voltage: ");
		printInt10(voltage);
		printStr("\n");
		delay(200);

		IFS1bits.AD1IF = 0;			//reset A/D interrupt flag (conversion finished)

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
