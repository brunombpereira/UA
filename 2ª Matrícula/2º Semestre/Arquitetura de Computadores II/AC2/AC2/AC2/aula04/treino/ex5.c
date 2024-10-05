#include <detpic32.h>

int main(void){
	static const char display7Scodes[] = {0x3F, 0x06, 0x5B,0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
	TRISB = (TRISB & 0x80FF)|0x000F;		//0000 0000 0000 1111
	PORTB = PORTB & 0x000F;
	LATB = LATB & 0X80FF;
	
	TRISD= TRISD & 0xFF9F;
	LATD = LATD & 0xFF9F;	

	LATD= (LATD & 0xFF9F)|0xFFCF;			// 1111 1111 1101 1111

	while(1){
		int input = PORTB & 0x000F;			//envia para o input o que é lido das entradas RB0-3
		char output = display7Scodes[input];		//Conversão de bin para 7S_code
		LATB = output << 8;				//Envia para os displays (RB8-14) os 8 bits menos
							  			//significativos do que é lido nos Dipswitch
	
	
	}
	return 0;
}
