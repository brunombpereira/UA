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
volatile unsigned char voltage = 0;

int main(void){

			
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
			// Configure interrupt system
			EnableInterrupts();	// Global Interrupt Enable
			AD1CON1bits.ASAM = 1;	// Start A/D conversion
			
			unsigned int cnt=0;
			while(1)
			{
				if(cnt % 25 == 0)// 250 ms (4 samples/second)
				{ 
				AD1CON1bits.ASAM = 1;// Start A/D conversion
				}
				cnt++ ;
					// Wait 10 ms
			}
			return 0;
}

// Interrupt Handler
void _int_(27) isr_adc(void) ////Replace VECTOR by the A/D
 {									//vector number - see "PIC32
 	//printInt(ADC1BUF0, 16 | 3<<16);					// family datasheet" (pages 74-76)
	int soma=0;
 	int *p = (int *)(&ADC1BUF0);
	for(; p <= (int *)(&ADC1BUF7); p+=4 )
	{
		printInt( *p, 16 | 4 << 16 );
		soma += *p;
		printf(" ");
	}
	printf(" \n");
	int media=soma/8;
	int v= (media*33+511)/2024;
	voltage= bintoBCD(v);
	// Send "voltage" variable to displays
	IFS1bits.AD1IF = 0;
}

         // função para converter para BCD //
unsigned char bintoBCD(unsigned char value){
   return ((value/10) << 4) + (value % 10); 

}
