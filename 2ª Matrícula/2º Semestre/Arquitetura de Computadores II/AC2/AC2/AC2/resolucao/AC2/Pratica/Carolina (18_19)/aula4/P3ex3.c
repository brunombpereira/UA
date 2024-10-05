#include <detpic32.h>

void send2displays(unsigned char);
void delay(int);

unsigned char bintoBCD( unsigned char );

int main(void)
{

	LATDbits.LATD6 = 0;			// display high
	LATDbits.LATD5 = 0;			// display low	
	TRISB = (TRISB & 0x00FF);	// configure RB8 to RB15 and RD5 to RD6 as outputs
	
	TRISD = (TRISD & 0xFF9F);



	unsigned char counter = 0,i;

	while(1)
	{
		i = 0;
		
	
		do
		{
			delay(10);// freq 1hz
			send2displays(bintoBCD(counter));

		} while (++i<100);
		

		if(counter != 59) 
			counter++;
		else {
			counter = 0;
		}

		
	}
		return 0;
}

	




void send2displays(unsigned char value){
	static const char display7Scodes[] ={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
	static int flag=0;
	int hi=value >>4;
	int lo=value & 0x0F;


	//ativa alternadamente(um de cada vez e envia o hi e o lo)
	if(flag!=0)
	{//send digit to high display	

		LATB = (LATB & 0x80FF) | display7Scodes[hi]<<8;
		LATDbits.LATD6=1;
		LATDbits.LATD5=0;

		LATBbits.LATB15=0;
		if (value % 2 ==0)
		{
			LATBbits.LATB15=1;
		}
	}
	else
	{
		LATB = (LATB & 0x80FF) | display7Scodes[lo]<<8;
		LATDbits.LATD6=0;
		LATDbits.LATD5=1;

		LATBbits.LATB15=0;
		if (value % 2 !=0)
		{
			LATBbits.LATB15=1;
		}
	}
	flag = ~flag;
}

unsigned char bintoBCD( unsigned char value)
{
	return(((value/10)<<4)| value%10);
}

void delay(int ms)
{
	
	for(; ms > 0; ms--)
		
		{	
			resetCoreTimer();
			while(readCoreTimer() < 20000);
		}

}

