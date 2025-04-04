#include <detpic32.h>

void delay(int ms){
	for(; ms > 0 ;ms--){
	resetCoreTimer();
	while(readCoreTimer() < 20000);
	}

}
int main (void){	
			TRISEbits.TRISE0 = 0;	//configure o porto RE0 como saída

			TRISBbits.TRISB4 = 1;	  // RB4 configured as input
			AD1PCFGbits.PCFG4 = 0;    // RB4 configured as analog 
			AD1CON1bits.SSRC = 7;     //modo "auto convert"
			AD1CON1bits.CLRASAM = 1;  //so há conversão quando se dá ordem 
					          //  interrupt is generated. At the same time, 
		                                  //  hardware clears the ASAM bit 
			AD1CON3bits.SAMC = 16;    // Sample time is 16 TAD (TAD = 100 ns) 
			AD1CON2bits.SMPI = 0;     // Interrupt is generated after XX samples (XX-1)
		                                  //  (replace XX by the desired number of 
		                                  //  consecutive samples)  
					          // informação disponível no registo(ADC1BUFXX-1)
			AD1CHSbits.CH0SA = 4;     // replace x by the desiredinput  
		                                  //  analog channel (0 to 15) 
			AD1CON1bits.ON = 1;       // Enable A/D converter 
	                                  //  This must the last command of the A/D
	                                  //  configuration sequence input (AN4) 
			IPC6bits.AD1IP = 2; // configure priority of A/D interrupts
			IFS1bits.AD1IF = 0; // clear A/D interrupt flag
			IEC1bits.AD1IE = 1; // enable A/D interrupts
			
	//config displays e os respetivos RB	
	TRISD = (TRISD & 0xFF9F);
	TRISB = TRISB & 0x00FF;
	int i;
	LATDbits.LATD6 = 1;	
	LATDbits.LATD5 = 0;
	int level;
	unsigned char array[] = {0x40, 0x01, 0x02,  0x80, 0x04, 0x10, 0x20,0x40, 0x80};
	int tempo[] = {250, 500, 750, 1000, 1250, 1500, 1750, 2000};
	while(1){	
		i=0;
		for(; i<7; i++)	{

		AD1CON1bits.ASAM = 1;
		while(IFS1bits.AD1IF ==0);

	
		level = (ADC1BUF0* 8)/1024;
			
			LATB = (LATB & 0x00FF ) | array[i]<<8;
			printInt10(level);
			delay( tempo[level]);
			}	
		IFS1bits.AD1IF=0;
	}
	
return 0;
}
