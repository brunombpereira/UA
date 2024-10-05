#include <detpic32.h>
void setPWM(unsigned int dutycycle);	

int main(void){
	T3CONbits.TCKPS = 4;
	PR3= 12499;
	TMR3=0;
	T3CONbits.TON = 1;
	
	OC1CONbits.OCM = 6;
	OC1CONbits.OCTSEL = 0;
	setPWM(25);			//OC1RS = (dutycycle*(prx+1))/100
	OC1CONbits.ON = 1;
	
	TRISD = TRISD & 0xF7FF;		//1111 0111 1111 1111
	LATD = LATD & 0xF7FF;
	PORTD = PORTD & 0x0001;			//0000 0000 0000 0001
	
	while(1){
		LATD = (LATD & 0xF7FF) | PORTD;
	}
	return 0;
}

void setPWM(unsigned int dutycycle){
	if((dutycycle>=0) && (dutycycle<=100)){
		OC1RS = (dutycycle*(PR3+1))/100;
	}
}
