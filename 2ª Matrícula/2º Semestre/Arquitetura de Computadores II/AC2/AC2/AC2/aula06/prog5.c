#include <detpic32.h>

int main(void){

	TRISBbits.TRISB4 = 1;
	AD1PCFGbits.PCFG4 = 0;
	AD1CON1bits.SSRC=7;
	AD1CON1bits.CLRASAM = 1;
	AD1CON3bits.SAMC = 16;
	AD1CON2bits.SMPI =16-1;
	AD1CHSbits.CH0SA=4;
	AD1CON1bits.ON=1;
	
	volatile int val_ad = 0;
	int v;
	while(1){
		AD1CON1bits.ASAM = 1; 			//STARTS CONVERTION
		while(IFS1bits.AD1IF == 0);		//WAIT FO END OF CONVERSION
		int *p = (int *)(&ADC1BUF0);		//READ ADC VALUE
		for(; p<= (int *) (&ADC1BUFF); p+=4){
			printInt(*p,10|4<<16);
			putChar(' ');
			val_ad+=*p;
		}
		val_ad = val_ad/16;
		v = (val_ad*33+511)/1013;
		putChar('>');
		printInt(v,10|4<<16);
		IFS1bits.AD1IF = 0;
		putChar('\n');
	}	
	return 0;
}
