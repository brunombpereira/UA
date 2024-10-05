#include <detpic32.h>

volatile int adc_value;


// Interrupt Handler
void _int_(27) isr_adc(void)	// Vector number ADC1 page 75
{

	adc_value = ADC1BUF0;
		

	AD1CON1bits.ASAM = 1;	// Start conversion

	IFS1bits.AD1IF = 0;		// Reset AD1IF flag


	LATEbits.LATE0 = 1;	// Set digital output = 1.

}



int main()
{

	// RB4 configuration:

	TRISBbits.TRISB4 	= 1; 	// Digital -> input
	AD1PCFGbits.PCFG4  	= 0; 	// RB4 config as analog input
	AD1CON1bits.SSRC 	= 7; 	// ADC conversion config bits, mode 7
	AD1CON1bits.CLRASAM = 1; 	// conversions be4 interrupt is generated
	AD1CON3bits.SAMC    = 16;	// Sample time is 16 TAD (TAD = 100 ns)
	AD1CON2bits.SMPI	= 3;	// Interrupt is generated after x - 1 samples.
	AD1CHSbits.CH0SA	= 4;	// Desired adc input

	AD1CON1bits.ON		= 1;	// Enable adc (last command)


	LATEbits.LATE0 = 0;		// Set digital output = 0.
	TRISEbits.TRISE0 = 0;	// Digital output for time measurement	


	// Interupt configuration:	Specific bits in the datasheet

	IPC6bits.AD1IP = 2;		// configure priority of A/D interrupts
	IFS1bits.AD1IF = 0;		// clear A/D interrupt flag
	IEC1bits.AD1IE = 1;		// enable A/D interrupts

	EnableInterrupts();

	AD1CON1bits.ASAM = 1;	// Start conversion

	while(1) {LATEbits.LATE0 = 0;}	// Set digital output = 0.

	return 0;

}
