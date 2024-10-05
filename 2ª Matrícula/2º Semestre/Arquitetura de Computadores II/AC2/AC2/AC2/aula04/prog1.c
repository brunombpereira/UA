#include <detpic32.h>

int main(void){
	TRISCbits.TRISC14 = 0; //CONFIGURA O PORTO RC14 COMO OUT
	//alternativa: TRISC=TRISC & 0xBFFF
	LATCbits.LATC14=0;	
	//ALTERNATIVA: LATC = LATC & 0xBFFF;
	while(1){
		resetCoreTimer();
		while(readCoreTimer()<10000000);
		
		LATCbits.LATC14 = !LATCbits.LATC14;
		//LATC = LATC ^ 0x4000;
	}
}
