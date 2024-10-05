#include <detpic32.h>

int main(void){
	//Configurar o timer2 com dutycycle variavel
	T2CONbits.TCKPS = 2;
	PR2 = ((20000000/4)/150)-1;
	TMR2 = 0;
	T2CONbits.TON = 1;
	
	OC2CONbits.OCM = 6;
	OC2CONbits.OCTSEL = 0;
	OC2RS = ((PR2+1)*100)/100;		//valor inicial dutycyle a 100 %
	OC2CONbits.ON = 1; 
	
	//Configurar porto rd3 e rd0 como input
	TRISB = TRISB & 0x0009;		//0000 0000 0000 1001
	PORTB = PORTB & 0x0009;
	
	
	
	while(1){
		
		if(PORTB == 0x0001){
			OC2RS = ((PR2+1)*25)/100;		//valor do dutycyle passa a 25 %
		}
		if(PORTB == 0x0008){
			OC2RS = ((PR2+1)*70)/100;		//valor do dutycyle passa a 25 %
		}
	
		resetCoreTimer();
		while(readCoreTimer()<20000000*(0.00025));
	
	}

	return 0;
}
