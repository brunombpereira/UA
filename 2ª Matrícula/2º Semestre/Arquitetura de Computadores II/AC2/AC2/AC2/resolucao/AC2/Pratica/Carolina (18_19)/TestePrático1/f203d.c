#include <detpic32.h>

typedef unsigned char uchar;
typedef unsigned int uint;


void init(void){
	TRISB &= 0xFC00; // define RB0 - RB9 output
			 // OUTPUT = 0 | INPUT = 1 
	TRISBbits.TRISB14  = 1; // RB14 as output	
}// init

enum RBBits{
  B = 0x01, //RB0
  A = 0x02, //RB1
  F = 0x04, //RB2
  G = 0x08, //RB3
  E = 0x10, //RB4
  D = 0x20, //RB5
  C = 0x40, //RB6
  H = 0x80, //RB7
  // Display Selector
  S_HI = 0x0100, //RB8
  S_LO = 0x0200, //RB9
};


void send2displays(unsigned char value)
{	
	static const unsigned char display7Scodes[]= {F,A,B,E,D,C,B,A,F,C,D,E};

	uchar digit_low = value & 0x0F;
	uchar digit_high = value >> 4;
	
	LATB &= 0xFC00; 		//clear old values
	LATB |= display7Scodes[value];	 

	if(value == 0 || value == 1 || value == 2 || value == 9 || value == 10 || value == 11  )
	{
	 LATBbits.LATB9 = 1;
	
	}else{
	 LATBbits.LATB8 = 1;
	}//if
	
	

}// send2displays


void configAD(uint samples){

AD1CON1bits.SSRC = 7;

AD1CON1bits.CLRASAM = 1;
AD1CON3bits.SAMC = 16;
AD1CON2bits.SMPI = samples-1;
AD1CHSbits.CH0SA = 14;
AD1CON1bits.ON = 1;

IFS1bits.AD1IF = 0; // reset flag


//------

IPC6bits.AD1IP = 3;
IEC1bits.AD1IE = 1;
EnableInterrupts();


}//configAD

volatile uint delaytime = 0;
void _int_(27) isr_adc(void)
{
	 if(ADC1BUF0 <127.875){
		delaytime = 1;	
	 }else if(ADC1BUF0 >127.877 && ADC1BUF0 < 2*127.877){
		delaytime = 2;
	 }else if(ADC1BUF0>2*127.877 && ADC1BUF0 < 3*127.877){
		delaytime = 3;
	 }else if(ADC1BUF0 >3*127.877 && ADC1BUF0 < 4*127.877){
		delaytime = 4;
	 }else if(ADC1BUF0 >4*127.877 && ADC1BUF0 < 5*127.877){
		delaytime = 5;
	 }else if(ADC1BUF0 >5*127.877 && ADC1BUF0 < 6*127.877){
		delaytime = 6;
	 }else if(ADC1BUF0>6*127.877 && ADC1BUF0 < 7*127.877){
		delaytime = 7;
	 }else if(ADC1BUF0>7*127.877 && ADC1BUF0 < 8*127.877){
		delaytime = 8;
	 } // if


IFS1bits.AD1IF = 0; //RESET FLAG
}


unsigned char toBcd(unsigned char value)
{
	return ((value / 10) << 4) + (value % 10);
}//toBcd

void delay(uint time){
	while(readCoreTimer() < time* (PBCLK/1000));
	resetCoreTimer();
}//delay



// -------------------------------------------------

void main(void){
	init();
	configAD(1);
	uchar value = 0;
	uint delays[]={250,2*250,3*250,4*250,5*250,6*250,7*250,8*250};
	while(1)
	{
	 AD1CON1bits.ASAM = 1; //Start Conversion	
	 	
	 delay(delays[delaytime]); 
	 send2displays(value);
	 
 	if(++value == 0x000C){
	value = 0;
	}//if
	 
	IFS1bits.AD1IF = 0;
	} //infinit loop 
}//void



