#include <detpic32.h>

void main(void){
	TRISB = (TRISB & 0x80FF ) | 0x00F;		//SW
	TRISDbits.TRISD6 = 0;
	TRISE = TRISE & 0xFFF0;				//LEDS
	while(1){
		//ler o switch
		int sw = PORTB & 0x000F;

		LATE = (LATE & 0xFFF0) | sw;
	}
	
}
