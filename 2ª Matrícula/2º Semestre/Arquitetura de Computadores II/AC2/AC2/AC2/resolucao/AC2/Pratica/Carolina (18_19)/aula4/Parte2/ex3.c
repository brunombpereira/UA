#include <detpic32.h>

void send2displays(unsigned char value);
 void delay(int ms) ;

int main(void)
{
	static const char display7Scodes[] = {0x3F, 0x06, 0x5B,0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
	
		TRISB= (TRISB & 0x80FF) | 0x000F;	// configure RB0 to RB3 as inputs	
											// configure RB8 to RB14 
	//configure RD5 to RD6 as outputs
		TRISDbits.TRISD5= 0;
		TRISDbits.TRISD6= 0;
	// Select display low
		LATDbits.LATD5=1;
		LATDbits.LATD6=0;
	while(1)
	{
		for (int i = 0; i < 128; ++i)
		{
			send2displays(i);
			delay(200);
		}
		
	}
	return 0;

}

void send2displays(unsigned char value)
{
	static const char display7Scodes[16] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
					  					    0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

	int dh = value>>4;
	int dl = value & 0x0F;
	

}


 void delay(int ms) 
{ 
  for(; ms > 0; ms--) 
  { 
    resetCoreTimer(); 
  while(readCoreTimer() < 20000); 
    } 
} 
