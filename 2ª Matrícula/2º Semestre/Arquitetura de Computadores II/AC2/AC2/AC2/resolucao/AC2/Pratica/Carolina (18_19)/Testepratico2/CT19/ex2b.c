//Oc3 a 200hz e o valor do dutycycle era o do potenciometro
#include <detpic32.h>
void send2displays(unsigned char value);
unsigned char bin2BCD(unsigned int value);

void configTim(){
	T3CONbits.TCKPS = 1;			//kprec=1,52<2
	PR3 = 49999;					//10000000/200-1
	TMR3 = 0;
	T3CONbits.TON = 1;

	IPC3bits.T3IP = 2;
	IEC0bits.T3IE = 1;
	IFS0bits.T3IF = 0;

	OC3CONbits.OCM = 6; 
	OC3CONbits.OCTSEL =1;

	OC3CONbits.ON = 1;

}

volatile int count=0;
volatile int conta=0;
volatile int ADC=0;

void _int_(12) isr_T3(void){
	AD1CON1bits.ASAM = 1;
	OC3RS = ((49999+1)*ADC)/100;
	printInt10(ADC);
	send2displays(bin2BCD(4));			//200hz
	IFS0bits.T3IF = 0;

}

void configADC(){


	TRISBbits.TRISB4 = 1;     // RBx digital output disconnected 
	AD1PCFGbits.PCFG4= 0;     // RBx configured as analog input (AN4)    
	AD1CON1bits.SSRC = 7;     // Conversion trigger selection bits: in this                              //  mode an internal counter ends sampling and                              //  starts conversion    
	AD1CON1bits.CLRASAM = 1;  // Stop conversions when the 1st A/D converter                              //  interrupt is generated. At the same time,                              //  hardware clears the ASAM bit    
	AD1CON3bits.SAMC = 16;    // Sample time is 16 TAD (TAD = 100 ns)    
	AD1CON2bits.SMPI = 1-1;  // Interrupt is generated after XX samples                              //  (replace XX by the desired number of                              //  consecutive samples)    
	AD1CHSbits.CH0SA = 4;     // replace x by the desired input                               //  analog channel (0 to 15)    
	AD1CON1bits.ON = 1;       // Enable A/D converter //  This must the last command of the A/D                             //  configuration sequence 

	//interrupçoes
	IPC6bits.AD1IP = 2;
	IFS1bits.AD1IF = 0;
	IEC1bits.AD1IE = 1;

	TRISDbits.TRISD6 = 0;
	TRISDbits.TRISD5 = 0;
	LATDbits.LATD6 = 1;
	LATDbits.LATD5 = 1;


}	
void _int_(27) isr_adc(void){
	ADC = (ADC1BUF0*100 +511)/1023;
	IFS1bits.AD1IF = 0;
	}
 
unsigned char bin2BCD(unsigned int value){
	return (((value/10)<<4) + (value%10));

}
volatile int flag=0;

void send2displays(unsigned char value){

	static const char array[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D,  0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

	int hd = value >>4;
	int ld = value & 0x0F;
	if(flag==0){
		LATDbits.LATD6=1;
		LATDbits.LATD5=0;
		TRISB = (TRISB & 0x00FF) |array[hd]<<8;
	}
	else{
		LATDbits.LATD6=0;
		LATDbits.LATD5=1;
		TRISB = (TRISB & 0x00FF) |array[ld]<<8;
	}
	flag= !flag;
}

int main(void){
	TRISB = (TRISB & 0x00FF);

	configTim();
	configADC();
	EnableInterrupts();	
	while(1){
		}
	return 0;		
}

//	ADC = (ADC1BUF0*100 +511)/1023;

