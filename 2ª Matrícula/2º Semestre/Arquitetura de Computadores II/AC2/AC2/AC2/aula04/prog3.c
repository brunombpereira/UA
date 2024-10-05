#include <detpic32.h>

int main(void){
	TRISB = TRISB & 0x80FF;//1000 0000 1111 1111
	LATB = LATB & 0x80FF;
	TRISD = TRISD & 0xFF9F;  //1111 1111 1001 1111
	LATD = LATD & 0xFF9F;
	
	while(1){
		LATD = LATD | 0xFFBF; //1111 1111 1011 1111  
		char input= getChar();
		if(input=='a' || input=='A'){
			LATB = (LATB & 0x80FF)|0x0100;	
		}
		if(input=='b' || input=='B'){
			LATB = (LATB & 0x80FF)|0x0200;	
		}


	}



}
