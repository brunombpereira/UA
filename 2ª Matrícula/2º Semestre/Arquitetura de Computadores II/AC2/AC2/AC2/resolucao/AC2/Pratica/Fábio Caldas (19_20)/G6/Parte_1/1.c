#include <detpic32.h>
#define SAMPLES 1
void delay(int ms);

void configPorts()
{

}

void configADC()
{
	TRISBbits.TRISB4 = 1;
	AD1PCFGbits.PCFG4 = 0;
	AD1CON1bits.SSRC = 7;
	AD1CON1bits.CLRASAM = 1;
	AD1CON3bits.SAMC = 16;
	AD1CON2bits.SMPI = SAMPLES-1;
	AD1CHSbits.CH0SA = 4;
	AD1CON1bits.ON = 1;

	//IS config
	IPC6bits.AD1IP = 2;	// A/D interrupt priority
	IFS1bits.AD1IF = 0;	// reset A/D interrupt flag
	IEC1bits.AD1IE = 1;	// Enable A/D interrupts
}

int main(void)
{
	configPorts();
	configADC();

	EnableInterrupts();

	AD1CON1bits.ASAM = 1;

	while(1)
	{

	}

	return 0;
}

//Interrupt handler
void _int_(27) isr_adc(void)
{
	printInt(ADC1BUF0, 16 | 3 << 16);
	printStr("\n");
	delay(200);
	AD1CON1bits.ASAM = 1;	//Start A/D conversion
	IFS1bits.AD1IF = 0;
}

void delay(int ms)
{
	for(; ms > 0; ms--)
	{
		resetCoreTimer();
		while(readCoreTimer() < 20000);
	}
}
