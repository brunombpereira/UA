#include <detpic32.h>

int main(void){
	TRISB = TRISB & 0x80FF;		//1000 0000 1111 1111
	LATB = LATB & 0x80FF;

	TRISD = TRISD & 0xFF9F; 		//1111 1111 1001 1111
	LATD = LATD & 0xFF9F;
	int i;
	unsigned char segment;
	while(1){
		LATD= (LATD & 0xFF9F) | 0xFFBF; 		//1111 1111 1011 1111
		segment=1;
		for(i = 0; i<7;i++){
			LATB=(LATB & 0x80FF)|(segment<<8);
			resetCoreTimer();
			while(readCoreTimer()<20000000*0.01);
			segment = segment<<1;
		}
	}
}
