#include <detpic32.h>
void send2displays(unsigned char);
unsigned char bintoBCD( unsigned char value);

volatile unsigned char voltage = 0;		// Global variable


int main(void){

	T3CONbits.TCKPS = 2;
	PR3 = 49999;
	TMR3 = 0;
	T3CONbits.TON = 1;

	//duty clycle
	OC1CONbits.OCM	=	6;
	OC1CONbits.OCTSEL = 0;
	OC1RS = 125000;
	OC1CONbits.ON = 1;

	while(1);

return 0;
}

