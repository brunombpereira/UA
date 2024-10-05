#include <detpic32.h>
void setPWM(unsigned int dutyCycle);

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
	setPWM(1);
	OC1CONbits.ON = 1;
	
	//CONFIGURAR PORTO RD0 E RC14
	TRISC = TRISC & 0xBFFF;		//1011 1111 1111 1111
	LATC = LATC & 0xBFFF;
	
	TRISD = TRISD & 0x0001;		//0000 0000 0000 0001
	PORTD = PORTD & 0x0001;
	
	while(1){
	LATCbits.LATC14 = PORTDbits.RD0;
	
	}
	return 0;
}

void setPWM(unsigned int dutyCycle){
	if ((dutyCycle>=0) & (dutyCycle<=100)){
		OC1RS = ((PR3+1)*dutyCycle)/100;
	}

}
