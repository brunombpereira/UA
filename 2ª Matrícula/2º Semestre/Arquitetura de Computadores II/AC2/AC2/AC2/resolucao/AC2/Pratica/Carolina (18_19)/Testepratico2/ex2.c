#include <detpic32.h>

int main(void){

	 static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D,  0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

	TRISB = (TRISB & 0x00FF ) | 0x00F;		//SW
	TRISDbits.TRISD6 = 0;
	TRISDbits.TRISD5 = 0;
	LATDbits.LATD6 = 1;
	LATDbits.LATD5 = 0;

	TRISE = TRISE & 0xFFF0;				//LEDS


	while(1){
		//ler o switch
		int sw = PORTB & 0x000F;

		LATE = (LATE & 0xFFF0) | sw;
		LATB = (LATB & 0x00FF) | display7Scodes[sw]<<8; 
	}
return 0;
}


