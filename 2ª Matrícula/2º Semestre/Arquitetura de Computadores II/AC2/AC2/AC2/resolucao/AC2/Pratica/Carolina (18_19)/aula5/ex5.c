#include <detpic32.h>
void delay(int);
void send2displays(unsigned char);
unsigned char bintoBCD( unsigned char value);

void delay(int ms) { 
	for(; ms > 0; ms--) { 
		resetCoreTimer(); 
		while(readCoreTimer() < 20000); 
   	} 
} 

int main(void){
	int i=0;
	int V;

			 TRISD=TRISDbits.TRISD5 =0; 
		   TRISD=TRISDbits.TRISD6 =0;

		   TRISB=(TRISB & 0x80FF) | 0x0001; //RB14-8 outputs RB0 input
			TRISBbits.TRISB4 = 1;	  // RB4 configured as input
			AD1PCFGbits.PCFG4 = 0;    // RB4 configured as analog 
			AD1CON1bits.SSRC = 7;     //modo "auto convert"
			AD1CON1bits.CLRASAM = 1;  //so há conversão quando se dá ordem 
					          //  interrupt is generated. At the same time, 
		                                  //  hardware clears the ASAM bit 
			AD1CON3bits.SAMC = 16;    // Sample time is 16 TAD (TAD = 100 ns) 
			AD1CON2bits.SMPI = 4-1;     // Interrupt is generated after XX samples (XX-1)
		                                  //  (replace XX by the desired number of 
		                                  //  consecutive samples)  
					          // informação disponível no registo(ADC1BUFXX-1)
			AD1CHSbits.CH0SA = 4;     // replace x by the desiredinput  
		                                  //  analog channel (0 to 15) 
			AD1CON1bits.ON = 1;       // Enable A/D converter 
	                                  //  This must the last command of the A/D
	                                  //  configuration sequence input (AN4) 

	while(1) {
		if(i++ % 25 == 0)
		{	//250 ms, 500 ms, 750 ms
			
		
			//ordem de conversão:
			AD1CON1bits.ASAM=1;	
			//polling: wait while conversion not done
			while(IFS1bits.AD1IF == 0);
		
			
			int soma=0;
			//nivel=(ADC1BUF0*5)/1024;
			//acesso as 16 posiçoes do buffer
			int *p = (int *)(&ADC1BUF0);
			for(; p <= (int *)(&ADC1BUFF); p+=4 )
			{
			printInt( *p, 16 | 4 << 16 );
			soma += *p;
			printf(" ");
			}
			int VAL_AD= soma/4;
			V=(VAL_AD*33+511)/1023;
			printf("%d\n",V );
			//reset AD1IF (after read)
			IFS1bits.AD1IF = 0;
			 
		}
		send2displays(bintoBCD(V));
		
		delay(10);
		
	}
	return 0;
}
//------------------------------------

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
