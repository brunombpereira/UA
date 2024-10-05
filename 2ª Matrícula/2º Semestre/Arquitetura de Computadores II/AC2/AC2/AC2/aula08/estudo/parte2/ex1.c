#include <detpic32.h>

int main(void){
// Configurar o porto RE0 controla o LED0
	TRISE = TRISE & 0xFFFE; 		//1111 1111 1111 1110
	LATE = LATE & 0xFFFE;
	
//Configurar o porto RD8 controla o pulsador INT1
	TRISD = TRISD & 0x0100;		//0000 0001 0000 0000
	PORTD = PORTD & 0x0100;
	
	
	while(1){
		while(PORTDbits.RD8==0);
		resetCoreTimer();
		while(readCoreTimer()<20000000*3){
			LATEbits.LATE0 = 1;
		}
		LATEbits.LATE0=0;
	}
	return 0;
}
