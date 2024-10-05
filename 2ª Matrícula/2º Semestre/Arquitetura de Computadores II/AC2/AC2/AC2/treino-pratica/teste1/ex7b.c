#include <detpic32.h>

int main(void){
	TRISBbits.TRISB4=1;
	AD1PCFGbits.PCFG4=0;
	AD1CON1bits.SSRC=7;
	AD1CON1bits.CLRASAM=1;
	AD1CON3bits.SAMC=16;
	AD1CON2bits.SMPI=1-1;
	AD1CHSbits.CH0SA=4;
	AD1CON1bits.ON=1;
	
	TRISB= TRISB & 0x000F;
	PORTB= PORTB & 0x000F;

	while(1){
	AD1CON1bits.ASAM=1;
	while(IFS1bits.AD1IF==0);
	int value = ADC1BUF0;
	IFS1bits.AD1IF=0;

	int freq = 1+(value/255);
	int T = 1/freq;

	int input = PORTB & 0x000F;	
	printStr("DS=");
	printInt10((input & 0x08) >> 3);
	printInt10((input & 0x04) >> 2);
	printInt10((input & 0x02) >> 1);
	printInt10((input & 0x01));
	
	resetCoreTimer();
	while(readCoreTimer()<20000*T);
	putChar('\r');
	}

	return 0;
}
