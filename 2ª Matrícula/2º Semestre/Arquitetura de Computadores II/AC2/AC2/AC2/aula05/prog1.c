#include <detpic32.h>

void send2displays(unsigned char value);

int main(void){
	TRISB = TRISB & 0x80FF;  //1000 0000 1111 1111
	LATB = LATB & 0x80FF;
	TRISD = TRISD & 0xFF9F;
	LATD = LATD & 0xFF9F;

	while(1){
		send2displays(0xAF);
		resetCoreTimer();
		while(readCoreTimer()<200000){}

	}
	return 0;
}

void send2displays(unsigned char value){
	static const char display7Scodes[]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

	static char displayFlag = 0;
	unsigned char dlow = value & 0x0F;
	unsigned char dhigh = value >> 4;

	if(displayFlag == 0){
		LATD = (LATD & 0xFF9F)|0x0020;		// 0000 0000 0010 0000
		LATB = (LATB & 0x80FF)| display7Scodes[dlow] <<8;
	}else{
		LATD = (LATD & 0xFF9F)|0x0040;		// 0000 0000 0100 0000
		LATB = (LATB & 0x80FF)| display7Scodes[dhigh]<<8;
	}
	displayFlag = !displayFlag;

}

