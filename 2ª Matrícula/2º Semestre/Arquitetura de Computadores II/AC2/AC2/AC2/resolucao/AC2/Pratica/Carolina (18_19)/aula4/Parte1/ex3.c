#include <detpic32.h>

void delay(int);

int main(void)
{
	int ler;
	TRISB = TRISB & 0x00FF; // 
	TRISDbits.TRISD5=0;
	TRISDbits.TRISD6=0;
	int array []={0x81,0x02, 0x04,0x08, 0x10,0x20, 0x40,0x80};
	LATDbits.LATD5=0;
	LATDbits.LATD6=1;	
	while(1)
	{

		do{
			printf("Insira um caracter\n");
			
			ler= getChar();

		}while((ler < 0x41) | (ler > 0x47));

		int seg = ler - 0x41;
		LATB = (LATB & 0x00FF) | ( array[seg]<<8);		
	}
	return 0;
}
