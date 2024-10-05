#include <detpic32.h>
void delay(int);
void send2displays(unsigned char);
unsigned char bintoBCD( unsigned char value);
int main (void)
{
	//TRISB = TRISB | 0x0003 ;// configure RB0 e RB1 as intputs
	// configure RD5-RD6 as outputs
	TRISB = (TRISB & 0x00FF)| 0x0003;
	TRISE = (TRISE & 0xFFFE);
	TRISDbits.TRISD5=0;
	TRISDbits.TRISD6=0;

	TRISCbits.TRISC14=0 ;	// configure RC14 as output
	int sec=0;
	int min=0;
	int horas=0;
	
	
	unsigned int counter=0;

	while(1){
		if (counter%100==0)
		{
			sec++;
			if(sec==60){
				min++; 
				
				sec=00;
				if(min==60 ){
					min=00;
					horas++;
					if (horas==24){
						horas=00;
					}
				}
			}
		}
		printInt(horas,10| 2<<16);
		printStr(":");

		printInt(min,10| 2<<16);
		
		printStr(":");
	

		printInt(sec,10| 2<<16);
		printStr("\r");

		counter++;
		delay(10);
		send2displays(bintoBCD(sec));
	}
	return 0;
}
#if 0	
		int sw= (PORTB & 0x0003);	// ler o switch
		switch(sw)
		{ 
			//SS
			case 0 :
			
			//printf("%d\n",sec );
			//delay(200);
			send2displays(sec);
				

			break;

			//MM
			case 1:
				
				send2displays(min);
				printStr("case1");
			break;

			// HH
			case 2 :
				
				send2displays(horas);
				printStr("case2");
			break;

			//HH e MM ( alternadamente 0-5 s cada)
			case 3 :
				send2displays(horas);
				delay(500);
				send2displays(min);

			break;
		}
		
	}	
	return 0;
}
#endif 
 void delay(int ms) 
{ 
  for(; ms > 0; ms--) 
  { 
    resetCoreTimer(); 
  while(readCoreTimer() < 20000); 
    } 
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
	}
	else
	{
		LATB = (LATB & 0x80FF) | display7Scodes[lo]<<8;
		LATDbits.LATD6=0;
		LATDbits.LATD5=1;
	}
	flag = ~flag;
}

unsigned char bintoBCD( unsigned char value)
{
	return(((value/10)<<4)| value%10);
}