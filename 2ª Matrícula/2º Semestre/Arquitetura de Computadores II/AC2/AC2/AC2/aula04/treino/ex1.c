#include <detpic32.h>

int main(void){
	TRISC = TRISC & 0xBFFF; 		//1011 1111 1111 1111
	LATC = LATC & 0xBFFF;
	while(1){
		resetCoreTimer();
		while(readCoreTimer()<10000000);	//0.5*20 000 000
		LATC= LATC ^ 0x4000; 		// 0100 0000 0000 0000
	}
	return 0;
}
