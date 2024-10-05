#include <detpic32.h>

void main(void){
	TRISB = TRISB | 0x000C;
	TRISE = TRISE & 0xFFFC;
	while(1){
		int sw= PORTB & 0x000C;
		printInt10(sw>>2);
		LATE = ( LATE & 0xFFFC ) | sw>>2;
	}
}
