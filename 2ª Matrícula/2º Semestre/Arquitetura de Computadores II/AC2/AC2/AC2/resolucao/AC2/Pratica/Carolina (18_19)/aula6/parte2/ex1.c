#include <detpic32.h>
void delay(int);
void send2displays(unsigned char);
unsigned char bintoBCD( unsigned char value);

volatile int adc_value;

void delay(int ms) { 
	for(; ms > 0; ms--) { 
		resetCoreTimer(); 
		while(readCoreTimer() < 20000); 
   	} 
} 
void send2displays(unsigned char value) {
   static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D,  0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
   static char displayFlag = 0;  
   int dh = value >> 4;
   int dl = value & 0x0F;


   if (displayFlag == 0)
   {
      LATDbits.LATD6 = 0;
      LATDbits.LATD5 = 1;
      LATB = (LATB & 0x00FF) | display7Scodes[dl] << 8;
   }else
   {
      LATDbits.LATD6 = 1;
      LATDbits.LATD5 = 0;
      LATB = (LATB & 0x00FF) | display7Scodes[dh] << 8;
      
   }
   displayFlag = !displayFlag;
}

int main(void){
			
			TRISE= (TRISE & 0xFFFE);
			TRISEbits.TRISE0 = 0;	//configure o porto RE0 como saída

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
			IPC6bits.AD1IP = 2; // configure priority of A/D interrupts
			IFS1bits.AD1IF = 0; // clear A/D interrupt flag
			IEC1bits.AD1IE = 1; // enable A/D interrupts
			// Configure interrupt system
			EnableInterrupts();	// Global Interrupt Enable
			AD1CON1bits.ASAM=1;	// Start A/D conversion
			while(1) { }		// all activity is done by the ISR
			return 0;
}

// Interrupt Handler
void _int_(27) isr_adc(void) ////Replace VECTOR by the A/D
 {									//vector number - see "PIC32
 									// family datasheet" (pages 74-76)
 		LATEbits.LATE0 = 0;
	// Print ADC1BUF0 value; Hexadecimal (3 digits format)
		adc_value = ADC1BUF0;
		LATEbits.LATE0 = 1;
		AD1CON1bits.ASAM=1;		// Start A/D conversion
		IFS1bits.AD1IF = 0;		 //Reset AD1IF flag
}

