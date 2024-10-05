#include <detpic32.h>

int main(void){

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
		AD1CON1bits.ASAM = 1; 			//STARTS CONVERTION
		while(IFS1bits.AD1IF == 0);		//WAIT FO END OF CONVERSION
		int value = ADC1BUF0;			//READ ADC VALUE
		IFS1bits.AD1IF = 0;			//RESET AD1IF BIT
		printInt(value, 16|3 <<16);
	}	








	return 0;
}
