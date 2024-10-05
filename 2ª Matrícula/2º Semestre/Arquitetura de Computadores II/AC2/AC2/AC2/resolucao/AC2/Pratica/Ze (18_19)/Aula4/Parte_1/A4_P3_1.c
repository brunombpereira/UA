#include <detpic32.h>

int main()
{

	// Set as output:
	TRISD = (TRISD & 0xFF9F);	// Set RD5 - 6
	TRISB = (TRISB & 0x00FF);	// Set RB8 - 15

	LATDbits.LATD5 = 1;			// CNTL_DISP_L
	LATDbits.LATD6 = 0;			// CNTL_DISP_H


	char in;
	int  out = 0x00;			// Initial value

	while(1)
	{

	LATB  = (LATB & 0x00FF) | (out << 8);	// shifts left 8 times to go from 8 to 16 bits

	in = getChar();

	if(in == 'a') 	   {out = 0b00000001;}
	else if(in == 'b') {out = 0b00000010;}
	else if(in == 'c') {out = 0b00000100;}
	else if(in == 'd') {out = 0b00001000;}
	else if(in == 'e') {out = 0b00010000;}
	else if(in == 'f') {out = 0b00100000;}
	else if(in == 'g') {out = 0b01000000;}
	else if(in == '.') {out = 0b10000000;}
	else    		   {out = 0x00;}
	
	}

	return 0;

}
