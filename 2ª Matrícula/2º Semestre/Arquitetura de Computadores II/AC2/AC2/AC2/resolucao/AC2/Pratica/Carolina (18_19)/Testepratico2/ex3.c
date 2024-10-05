#include <detpic32.h>
volatile int amp=0;
void send2displays(unsigned char value);
char bin2BCD(unsigned int value);

volatile int count=0;
void _int_(8) isr_T2(void)			//400/8=50hz
{
	printStr("ola\n");
	send2displays(bin2BCD(amp));
	if(++count ==8){
			AD1CON1bits.ASAM = 1;
			printStr("AQUI");

			amp = ((ADC1BUF0 * 70)+511) /1023;
			printStr("\n v=");
			printInt10(amp );
		
		count=0;
	}
	IFS1bits.AD1IF = 0;

}

char bin2BCD(unsigned int value){
	return (((value/10)<<4) + (value%10));

}
volatile int flag=0;

void send2displays(unsigned char value){
	static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D,  0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
	
	int hd = value>>4;
	int ld= value &0x0F;
	if(flag==0){
		LATDbits.LATD6 = 1;
		LATDbits.LATD5 = 0;
		LATB = (LATB & 0x00FF) | display7Scodes[hd]<<8;

	}
	else{
		LATDbits.LATD6 = 0;
		LATDbits.LATD5 = 1;

		LATB = (LATB & 0x00FF)|  display7Scodes[ld]<<8;
	}
	flag= !flag;


}
void configTim(void){
	T2CONbits.TCKPS = 1;			//Kprescaler=0,76
	PR2 = 49999;					//fre1 400
	TMR2 = 0;
	T2CONbits.TON = 1;
	IPC2bits.T2IP = 2;
	IEC0bits.T2IE = 1;
	IFS0bits.T2IF = 0;

	OC2CONbits.OCM = 6; 
	OC2CONbits.OCTSEL =0;
	OC2RS = 12500;					//dutycycle 25%
	
	OC2CONbits.ON = 1;
}
	int main(void){
		
		TRISBbits.TRISB4 = 1;     // RBx digital output disconnected 
		AD1PCFGbits.PCFG4= 0;     // RBx configured as analog input (AN4)    
		AD1CON1bits.SSRC = 7;     // Conversion trigger selection bits: in this                              //  mode an internal counter ends sampling and                              //  starts conversion    
		AD1CON1bits.CLRASAM = 1;  // Stop conversions when the 1st A/D converter                              //  interrupt is generated. At the same time,                              //  hardware clears the ASAM bit    
		AD1CON3bits.SAMC = 16;    // Sample time is 16 TAD (TAD = 100 ns)    
		AD1CON2bits.SMPI = 1-1;  // Interrupt is generated after XX samples                              //  (replace XX by the desired number of                              //  consecutive samples)    
		AD1CHSbits.CH0SA = 4;     // replace x by the desired input                               //  analog channel (0 to 15)    
		AD1CON1bits.ON = 1;       // Enable A/D converter //  This must the last command of the A/D                             //  configuration sequence 
		configTim();
		TRISDbits.TRISD6 = 0;
		TRISDbits.TRISD5 = 0;
		LATDbits.LATD6 = 1;
		LATDbits.LATD5 = 1;


		TRISB = (TRISB & 0x00FF ) | 0x00F;		//SW
		//TRISE = TRISE & 0xFFF0;				//LEDS

		EnableInterrupts();

		while(1);
	return 0;
	}

