#include <detpic32.h>

void delay(int);

int main(void)
{
	TRISE = (TRISE & 0xFFF0); // RD0 configured as output
	int i=0;
	
	for (; i < 16; ++i)
	{
		LATE=(LATE & 0xFFF0) | i;

		delay(1000);
	}
	return 0;
}


   
   void delay(int ms) 
{ 
	for(; ms > 0; ms--) 
	{ 
		resetCoreTimer(); 
	while(readCoreTimer() < 20000); 
   	} 

} 
