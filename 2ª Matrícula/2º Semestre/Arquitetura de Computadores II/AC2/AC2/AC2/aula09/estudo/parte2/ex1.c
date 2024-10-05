#include <detpic32.h>

int main(void){
//duty cycle no timer
//OC1RS = ((PRx+1)*dutycycle)/100;


	//CONFIGURAR O TIMER 3 A 100Hz
	T3CONbits.TCKPS = 2;
	PR3 = 49999;
	TMR3 = 0;
	T3CONbits.TON = 1;
	
	OC1CONbits.OCM = 6;
	OC1CONbits.OCTSEL = 1;
	OC1RS = ((PR3+1)*25)/100;
	OC1CONbits.ON = 1;
	
	while(1);
	return 0;
}
