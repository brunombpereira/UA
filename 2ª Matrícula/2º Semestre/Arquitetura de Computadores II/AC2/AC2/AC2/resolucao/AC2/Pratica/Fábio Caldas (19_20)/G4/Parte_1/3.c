#include <detpic32.h>

void delay(int ms);

void configPorts()
{
	LATB = LATB & 0x00FF;	//RB8-15 = 0;
	TRISB = TRISB & 0x00FF; //RB8-15 Outputs (Disp7Seg c/ o "."(RB15))

	LATD = LATD & 0xFF9F;	//RD5-6 = 0;
	TRISD = TRISD & 0xFF9F; //RD5-6 Outputs

	LATDbits.LATD5 = 1;		//display_low, on;
	LATDbits.LATD6 = 0;		//display_high, off;
}

int main(void)
{
	configPorts();

	char input;

	while(1)
	{
		LATDbits.LATD5 = !LATDbits.LATD5;
		LATDbits.LATD6 = !LATDbits.LATD6;

		input = getChar();	//Ler do teclado
		switch(input)
		{
			case 'a':
				LATBbits.LATB8 = 1;
				break;
			case 'b':
				LATBbits.LATB9 = 1;
				break;
			case 'c':
				LATBbits.LATB10 = 1;
				break;
			case 'd':
				LATBbits.LATB11 = 1;
				break;
			case 'e':
				LATBbits.LATB12 = 1;
				break;
			case 'f':
				LATBbits.LATB13 = 1;
				break;
			case 'g':
				LATBbits.LATB14 = 1;
				break;
			case '.':
				LATBbits.LATB15 = 1;
				break;
		}
	}

	return 0;
}

void delay(int ms)
{
	for(; ms > 0; ms--)
	{
		resetCoreTimer();
		while(readCoreTimer() < 20000);
	}
}
