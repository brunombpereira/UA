#include <detpic32.h>

int main(void){
	TRISB = TRISB & 0x80FF;		//1000 0000 1111 1111
	LATB = LATB & 0x80FF;

	TRISD = TRISD & 0xFF9F; 		//1111 1111 1001 1111
	LATD = LATD & 0xFF9F;
	
	while(1){
		LATD= (LATD & 0xFF9F) | 0xFFBF; 		//1111 1111 1011 1111
		char input = getChar();
		if(input=='a' || input=='A'){
			LATB = (LATB & 0x80FF)|0x0100;		//0000 0001 0000 0000
		}
		else if(input=='B' || input=='b'){
			LATB = (LATB & 0x80FF)|0x0200;
		}
		else if(input=='c' || input=='C'){
			LATB = (LATB & 0x80FF)|0x0400;
		}
		else if(input=='d' || input=='D'){
			LATB = (LATB & 0x80FF)|0x0800;
		}
		else if(input=='E' || input=='e'){
			LATB = (LATB & 0x80FF)|0x1000;
		}
		else if(input=='f' || input=='F'){
			LATB = (LATB & 0x80FF)|0x2000;
		}
		else if(input=='G' || input=='g'){
			LATB = (LATB & 0x80FF)|0x4000;
		}
		else if(input=='a' || input=='A'){
			LATB = (LATB & 0x80FF)|0x8000;
		}
		else{
			LATB= LATB & 0x80FF;
		}
	}
}
