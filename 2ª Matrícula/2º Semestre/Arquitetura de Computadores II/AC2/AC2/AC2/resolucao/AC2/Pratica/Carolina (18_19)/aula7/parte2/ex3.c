#include <detpic32.h>

void setPWM(unsigned int dutyCycle){

	if(dutyCycle<= 100 && dutyCycle>=0){
		OC1RS = ((49999+1) * dutyCycle)/ 100;
		int a= ((49999+1) * dutyCycle)/ 100;

		printInt10(a);
	}
}

int main(void){

	T2CONbits.TCKPS = 2; //1:4 prescaler 
	PR2 = 49999; 		//Fout = 20MHz / (4 * (49999 + 1)) = 10 Hz
	TMR2 = 0;			//Reset timer T2 count register
	T2CONbits.TON = 1;  //Enable timer T2 (must be the last command of the
	//timer configuration sequence)

	OC1CONbits.OCM = 6; //PWM mode on OCx; fault pin disabled
	OC1CONbits.OCTSEL =0;//Use timer T2 as the time base for PWM generation
	OC1RS = 12500;		//Ton constant

	OC1CONbits.ON = 1;	//Enable OC1 module

	setPWM(100);

return 0;
}

