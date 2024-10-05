#include <detpic32.h>

void configPort()
{
	LATB = LATB & 0xFFF0;	//RB0-3 = 0
	TRISB = TRISB | 0x000F;	//RB0-3 Inputs (Dipswitch)

	LATB = LATB & 0x80FF;	//RB8-14 = 0
	TRISB = TRISB & 0x80FF;	//RB8-14 Outputs (Disp7Seg)

	LATD = LATD & 0xFF9F;	//RD5-6 = 0
	TRISD = TRISD & 0xFF9F; //RD5-6 Outputs
}

int main(void)
{
	configPort();

	static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
	LATDbits.LATD5 = 1;	//Disp low activate

	int input;
	char output;

	while(1)
	{
		input = PORTB & 0x000F;			//envia para o input o que é lido das entradas RB0-3
		output = display7Scodes[input];	//Conversão de bin para 7S_code
		LATB = output << 8;				//Envia para os displays (RB8-14) os 8 bits menos
							  			//significativos do que é lido nos Dipswitch

	}

	return 0;
}
