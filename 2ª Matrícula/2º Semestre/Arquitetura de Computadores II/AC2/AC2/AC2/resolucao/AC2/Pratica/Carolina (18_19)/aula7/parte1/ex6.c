#include <detpic32.h>
void delay(int);
void send2displays(unsigned char);
unsigned char bintoBCD( unsigned char value);
void configureAll(void);
void delay(int ms) { 
	for(; ms > 0; ms--) { 
		resetCoreTimer(); 
		while(readCoreTimer() < 20000); 
   	} 
} 
volatile unsigned char voltage = 0;		// Global variable

int main(void){
		 	configureAll();
			IFS0bits.T1IF = 0;// Reset T1IF flag       
			IFS0bits.T3IF = 0;// Reset T3IF flag       
			
			IFS1bits.AD1IF = 0; //Reset AD1IF 	
			
			EnableInterrupts();	// Global Interrupt Enable
		while(1)
		{
			if (PORTBbits.RB0 && !PORTBbits.RB1) 	//RB0=1 eRB1=0
			{
			   IEC0bits.T1IE = 0;  // disable timer interrupts
		
			}
			else	 IEC0bits.T1IE = 1;    // Enable timer T3 interrupts
		}

	return 0;
}

void configureAll(void){	// Configure interrupt system


   T1CONbits.TCKPS = 3; // 1:32 prescaler (i.e. fout_presc =  KHz)    
   PR1 = 39062;         // Fout = (78125/2)-1   
   TMR1 = 0;            // Reset timer T3 count register    
   T1CONbits.TON = 1;   // Enable timer T3 (must be the last command of the 
                        //  timer configuration sequence)
   IPC1bits.T1IP = 2;   // Interrupt priority (must be in range [1..6]) 
 IEC0bits.T1IE = 1;   // Enable timer T3 interrupts    
  
   IFS0bits.T1IF = 0;   // Reset timer T3 interrupt flag 

 T3CONbits.TCKPS = 2; // 1:32 prescaler (i.e. fout_presc = 625 KHz)    
   PR3 = 49999;         // pr3 = 625000/10 
   TMR3 = 0;            // Reset timer T3 count register    
   T3CONbits.TON = 1;   // Enable timer T3 (must be the last command of the 
                        //  timer configuration sequence)
   IPC3bits.T3IP = 2;   // Interrupt priority (must be in range [1..6])    
   IEC0bits.T3IE = 1;   // Enable timer T3 interrupts    
   IFS0bits.T3IF = 0;   // Reset timer T3 interrupt flag 
			// Configure all (digital I/O, analog input, A/D module, interrupts)

  
			TRISDbits.TRISD5 = 0;
			TRISDbits.TRISD6 = 0;
			TRISB=(TRISB & 0x80FF) | 0x0003; //RB14-8 outputs RB0e RB1 input

			TRISBbits.TRISB4 = 1;	  // RB4 configured as input
			AD1PCFGbits.PCFG4 = 0;    // RB4 configured as analog 
			AD1CON1bits.SSRC = 7;     //modo "auto convert"
			AD1CON1bits.CLRASAM = 1;  //so há conversão quando se dá ordem 
					          //  interrupt is generated. At the same time, 
		                                  //  hardware clears the ASAM bit 
			AD1CON3bits.SAMC = 16;    // Sample time is 16 TAD (TAD = 100 ns) 
			AD1CON2bits.SMPI = 8-1;     // Interrupt is generated after XX samples (XX-1)
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
}
// Interrupt Handler
void _int_(27) isr_adc(void) ////Replace VECTOR by the A/D
{									//vector number - see "PIC32
 									// family datasheet" (pages 74-76)

	
		int soma=0;
		//nivel=(ADC1BUF0*5)/1024;
		//acesso as 16 posiçoes do buffer
		int *p = (int *)(&ADC1BUF0);
			for(; p <= (int *)(&ADC1BUF7); p+=4 )
			{
				printInt( *p, 16 | 4 << 16 );
				soma += *p;
				printf(" ");
			}
		int VAL_AD= soma/8;
		int V=(VAL_AD*33+511)/1023;
		printf("%d\n", V);
		voltage= V;

		IFS1bits.AD1IF = 0;		 //Reset AD1IF flag

}

//rotinas de serviço a interrupção dos timers 
  void _int_(4) isr_T1(void) {
  	AD1CON1bits.ASAM = 1;  
   IFS0bits.T1IF = 0;// Reset T1IF flag       
   }   

  void _int_(12) isr_T3(void){   
	  send2displays(bintoBCD(voltage));
  IFS0bits.T3IF = 0; // Reset T3 interrupt flag    
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

