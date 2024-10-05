#include <detpic32.h>

int main(void){

	//configurar portos
	TRISB = TRISB & 0x000F;		 //0000 0000 0000 1111
	LATB = LATB & 0x000F;

	TRISE = TRISE & 0xFFF0;		//1111 1111 1111 0000
	LATE = LATE & 0xFFF0;

	//ciclo infinito
	
	while(1){
		LATE = PORTB;


	}
	return 0;
}
