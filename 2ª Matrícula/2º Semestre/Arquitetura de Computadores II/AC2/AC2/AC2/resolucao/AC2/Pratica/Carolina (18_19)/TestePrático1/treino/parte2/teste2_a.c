#include <detpic32.h>

void delay(int ms){
	for(; ms > 0 ;ms--){
	resetCoreTimer();
	while(readCoreTimer() < 20000);
	}

}
int main (void){
	//config displays e os respetivos RB	
	TRISD = (TRISD & 0xFF9F);
	TRISB = TRISB & 0x00FF;
	int i;
	LATDbits.LATD6 = 1;	
	LATDbits.LATD5 = 0;

	unsigned char array[] = {0x40, 0x01, 0x02,  0x80, 0x04, 0x10, 0x20,0x40, 0x80};
	while(1){	
		i=0;
		for(; i<7; i++)	{
		LATB = (LATB & 0x00FF ) | array[i]<<8;
		delay(250);	//0.25 s
		}
	
	}

return 0;
}
