#include <detpic32.h>

void delay(int ms) { 
	for(; ms > 0; ms--) { 
		resetCoreTimer(); 
		while(readCoreTimer() < 20000); 
   	} 
} 

int main(void){
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
	int sum;
	int Voltage;
	while(1) {

		if(q++ % 25 == 0)
		{
		//ordem de conversão:
		AD1CON1bits.ASAM=1;	
		//polling: wait while conversion not done
		while(IFS1bits.AD1IF == 0);
		int i;
		int *p = (int *) (&ADC1BUF0);
		for( i= 0; i < 16; i++){
		//imprimir o resultado da conv. em hexadecimal formatado com 4 dígitos
		
		printInt(p[i*4], 16 | 4 << 16);
		printf("%s"," ");
		VAL_AD += p[i*4]
		}

		Voltage =  VAL_AD / 4;

		}
		send2displays(Voltage);
		delay(10);
		//reset AD1IF (after read)
		IFS1bits.AD1IF = 0;
		
	}
	return 0;
}


	
