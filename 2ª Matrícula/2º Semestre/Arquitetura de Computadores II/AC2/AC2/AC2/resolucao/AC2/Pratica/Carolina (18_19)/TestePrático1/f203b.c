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

void send2displays(unsigned char value, int High )
{	
	
	static const unsigned char display7Scodes[]= {F,A,B,G,E,D,C,G};

	uchar digit_low = value & 0x0F;
	uchar digit_high = value >> 4;
	
	LATB &= 0xFC00; //clear old values
	LATB |= display7Scodes[value];	 

	if(High == 1 )
	{
	 LATBbits.LATB8 = 1;
	
	}else{
	 LATBbits.LATB9 = 1 ;	
	}//if
	
	

}// send2displays


void configAD(uint samples){

AD1CON1bits.SSRC = 7;

AD1CON1bits.CLRASAM = 1;
AD1CON3bits.SAMC = 16;
AD1CON2bits.SMPI = samples-1;
AD1CHSbits.CH0SA = 14;
AD1CON1bits.ON = 1;

IFS1bits.AD1IF = 0;

}//configAD

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
	int media;
	int delays[]={250,500,750,1000,1250,1500,1750,2000};
	while(1)
	{

	 AD1CON1bits.ASAM = 1; //Start Conversion
	 while( IFS1bits.AD1IF == 0 ); // Wait while conversion not done
	 media = (ADC1BUF0+ADC1BUF1+ADC1BUF2)/3;
	 media = (media*8)/1023;
	
	 delay( delays[media]);

	 IFS1bits.AD1IF = 0;
	
	 send2displays(value,1);
	
	 value++;

 	if(value == 0x0008){
	value = 0;
	}//if
	
} //infinit loop 
}//void



