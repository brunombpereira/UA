#include <detpic32.h>

void delay(int);

void main(void){
	//RE0,RE1,RE2,R3 como saídas 
	//ou TRISEbits.TRISE0=0; ...
	TRISEbits.TRISE0=0;
	TRISEbits.TRISE1=0;
	TRISEbits.TRISE2=0;
	TRISEbits.TRISE3=0;
	//TRISE = (TRISE & 0xFFF0);
	LATE = 0;
	int i=0;
	while(1)
	{
		LATE=i;
		delay(125); //freq. atualização de 4Hz
		i=i+1;
		
	}
}

void delay(int ms) 
{ 
	for(; ms > 0; ms--) 
	{ 
		resetCoreTimer(); 
	while(readCoreTimer() < 20000); 
   	} 
} 
