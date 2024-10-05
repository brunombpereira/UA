#include <detpic32.h>

 void delay(int);
 void send2displays(unsigned char);
 unsigned char bintoBCD(unsigned char);


int main(void)
{
	//configuraçao
	TRISB = (TRISB & 0x00FF) | 0x0003;

	TRISE = (TRISB & 0xFFFE);
	TRISDbits.TRISD6=0;
	TRISDbits.TRISD5=0;
	int count=0;
	int ss=0;
	int mm=0;
	int hh=0;
	int todisp=0;
	int MouS=0;
	int led=0;
	while(1)
	{	
		if(count % 100 ==0){
		ss++;
		if(ss==60){
			mm++;
			ss=0;
			if(mm==60){
				hh++;
				mm=0;
				if(hh==24){
					hh=0;
				}
				
			}
		}
		}
	printInt(hh, 10 | 2<<16);
	printStr(":");

	printInt(mm, 10 | 2<<16);
	printStr(":");

	printInt(ss, 10 | 2<<16);
	printStr("\r");

	int sw= (PORTB & 0x0003) ;
	switch(sw){
		case 0:
			todisp= ss;
		break;
		
		case 1:
			todisp= mm;
		break;
		
		case 2:
			todisp=hh;
		break;

		case 3:
			if(count % 50 == 0){
				if(MouS==0){
					todisp = ss;
				}
				else{
					todisp = mm;
				}
			MouS = ~MouS;
			}
		break;
	}
	count++;
	delay(10);
	send2displays(bintoBCD(todisp));
	//leds
	
			if(count % 50 == 0){
				if(led==0){
					LATE = (LATE & 0x0000);
				}
				else{		
					LATE = LATE | 0x0001;
				}
			led = ~led;
			}
	
	}
}


 unsigned char bintoBCD(unsigned char value){
return( ((value/10)<<4) | (value%10) );
}

 void send2displays(unsigned char value){
static const char display7Scodes[] = {0x3F,0x06, 0x5B, 0x4F, 0x66,0x6D, 0x7D,0x07,0x7F,0x6F,0x77, 0x7C,0x39,0x5E, 0x79, 0x71};
	static int flag = 0;
	int hi = value>>4;
	int lo = value & 0x0F;

	if(flag!=0){	
		LATB = (LATB & 0x80FF) | display7Scodes[hi]<<8;
		LATDbits.LATD6 = 1;	
		LATDbits.LATD5 = 0;
	}
	else{	
		LATB = (LATB & 0x80FF) | display7Scodes[lo]<<8;
		LATDbits.LATD5 = 1;	
		LATDbits.LATD6 = 0;
	}
	flag = ~flag;
	
}

void delay(int ms){

	for(; ms > 0; ms--)
	{
		resetCoreTimer();
		while(readCoreTimer()<20000);
	}
}




 










