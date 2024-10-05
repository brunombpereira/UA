#include <detpic32.h>
#define SAMPLES 1
void delay(int ms);

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
	configADC();

	while(1)
	{
		AD1CON1bits.ASAM = 1;				//start conversion
		while(IFS1bits.AD1IF == 0);			//Polling
		delay(500);
		printInt(ADC1BUF0, 16 | 3 << 16);	//Read conversion, in HEX and formated with 3 digits
		printStr("\n");
		IFS1bits.AD1IF = 0;					//reset A/D interrupt flag (conversion finished)

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
