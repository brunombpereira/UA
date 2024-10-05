#include <detpic32.h>

typedef unsigned char uchar;
typedef unsigned int uint;


void init(void){
	TRISB &= 0xFC00; // define RB0 - RB9 output
			 // OUTPUT = 0 | INPUT = 1 	
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

unsigned char toBcd(unsigned char value)
{
	return ((value / 10) << 4) + (value % 10);
}//toBcd

void delay(uint time){
	resetCoreTimer();
	while(readCoreTimer() < time* 20 000);
}//delay



// -------------------------------------------------

void main(void){
	init();
	uchar value = 0;
	while(1)
	{
	 send2displays(value,1);
	 delay(250); //velocidade

	 value++;

 	if(value == 0x0008){
	value = 0;
	}//if
	 
	} //infinit loop 
}//void



