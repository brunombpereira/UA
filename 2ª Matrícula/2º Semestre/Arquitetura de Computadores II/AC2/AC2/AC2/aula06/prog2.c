#include <detpic32.h>

int main(void){
	volatile int aux;

	TRISDbits.TRISD11 = 0;
	AD1PCFGbits.PCFG11 = 1;
	TRISBbits.TRISB4 = 1;
	AD1PCFGbits.PCFG4 = 0;
	AD1CON1bits.SSRC=7;
	AD1CON1bits.CLRASAM = 1;
	AD1CON3bits.SAMC = 16;
	AD1CON2bits.SMPI =1-1;
	AD1CHSbits.CH0SA=4;
	AD1CON1bits.ON=1;
	
	while(1){
		AD1CON1bits.SSRC = 7;
		AD1CON1bits.ASAM = 1; 			// STARTS CONVERTION
		LATDbits.LATD11 = 1;			// SET LATD11
		while(IFS1bits.AD1IF == 0);		// WAIT FO END OF CONVERSION
		LATDbits.LATD11 = 0;			// RESET LATD11
		aux = ADC1BUF0;				// READ ADC VALUE
		IFS1bits.AD1IF = 0;			// RESET AD1IF BIT
	}	








	return 0;
}
