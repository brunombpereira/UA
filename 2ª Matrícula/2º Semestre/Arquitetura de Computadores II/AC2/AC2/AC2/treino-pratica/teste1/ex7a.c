#include <detpic32.h>

int main(void){
	
	TRISB = TRISB & 0x000F;
	PORTB= PORTB & 0x000F;
	
	while(1){
		int input = PORTB & 0x000F;
		putChar('\r');
		printStr("DS=");
		printInt10((input & 0x08) >> 3);
		printInt10((input & 0x04) >> 2);
		printInt10((input & 0x02) >> 1);
		printInt10((input & 0x01));


		resetCoreTimer();
		while(readCoreTimer()<20000);

	}
	
	
	return 0;
}
