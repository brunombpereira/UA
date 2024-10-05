#include <detpic32.h>

int main(void)
{

	// RB4 configuration:

	TRISBbits.TRISB4 	= 1; 	// Digital -> input
	AD1PCFGbits.PCFG4  	= 0; 	// RB4 config as analog input
	AD1CON1bits.SSRC 	= 7; 	// ADC conversion config bits, mode 7
	AD1CON1bits.CLRASAM = 1; 	// conversions be4 interrupt is generated
	AD1CON3bits.SAMC    = 16;	// Sample time is 16 TAD (TAD = 100 ns)
	AD1CON2bits.SMPI	= 0;	// Interrupt is generated after x - 1 samples.
	AD1CHSbits.CH0SA	= 4;	// Desired adc input

	AD1CON1bits.ON		= 1;	// Enable adc (last command)


	return 0;

}