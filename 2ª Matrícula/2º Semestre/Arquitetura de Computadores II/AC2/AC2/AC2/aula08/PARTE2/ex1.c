#include <detpic32.h>

int main(void){
	TRISE = TRISE & 0xFFFE;	//1111 1111 1111 1110
	LATE = LATE & 0xFFFE;
	TRISD = TRISD & 0x0100;	//0000 0001 0000 0000
	PORTDbits.RD8=0;

	
	while(1){
		while(PORTDbits.RD8==0);
		resetCoreTimer();
		while(readCoreTimer()<20000000*3){
			LATEbits.LATE0= 1;
		}
		LATEbits.LATE0=0;
		PORTDbits.RD8=0;
	
	}
	return 0;
}



