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
	AD1CON2bits.SMPI = 0;     // Interrupt is generated after XX samples (XX-1)
                                  //  (replace XX by the desired number of 
                                  //  consecutive samples)  
			          // informação disponível no registo(ADC1BUFXX-1)
	AD1CHSbits.CH0SA = 4;     // replace x by the desiredinput  
                                  //  analog channel (0 to 15) 
	AD1CON1bits.ON = 1;       // Enable A/D converter 
                                  //  This must the last command of the A/D
                                  //  configuration sequence input (AN4) 

	while(1) {
		//ordem de conversão:
		AD1CON1bits.ASAM=1;	
		//polling: wait while conversion not done
		while(IFS1bits.AD1IF == 0);
		int conv_value = ADC1BUF0;
		//imprimir o resultado da conv. em hexadecimal formatado com 3 dígitos
		printInt(conv_value, 16 | 3 << 16);
		printf("%s\n"," ");
		delay(1000);
		//reset AD1IF (after read)
		IFS1bits.AD1IF = 0;
		
	}
	return 0;
}
