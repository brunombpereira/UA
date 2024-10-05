#include <detpic32.h>
void send2displays(unsigned char);
unsigned char bintoBCD( unsigned char value);

volatile unsigned char voltage = 0;		// Global variable

void setPWM( unsigned int dutyCycle){
	if( dutyCycle<=100 && dutyCycle >=0) 
		OC1RS = ((49999+1)*dutyCycle)/100;

}


int main(void){

	T3CONbits.TCKPS = 2;
	PR3 = 49999;
	TMR3 = 0;
	T3CONbits.TON = 1;

	//duty clycle
	OC1CONbits.OCM	=	6;
	OC1CONbits.OCTSEL = 1;
	OC1RS = 12500;
	OC1CONbits.ON = 1;
	while(1){
		setPWM(90);
	}
return 0;
}

