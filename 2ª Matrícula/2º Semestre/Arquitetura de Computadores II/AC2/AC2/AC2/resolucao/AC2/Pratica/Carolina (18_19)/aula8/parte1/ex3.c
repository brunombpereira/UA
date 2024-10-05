#include <detpic32.h>
void putc(char byte2send);
void puts(char *str);
void delay(int ms)
{
	for(; ms > 0; ms--) {
		resetCoreTimer();
		while(readCoreTimer() < 20000);
	}
}
int main (void)
{
	U1MODEbits.BRGH=0; 	//config baudrate  //taxa transm =16 logo->0
	U1BRG=10;

	U1MODEbits.PDSEL=0;		//paridade: sem paridade
	U1MODEbits.STSEL=0;		//nº Stop bits=1

	U1STAbits.UTXEN = 1;		//ativar modulos de transmissao
	U1STAbits.URXEN = 1;		//ativar modulos de recessao

	U1MODEbits.ON = 1;		//ativar UART

	while(1){
		puts("String de teste \n");
		delay(1000);

	}
	return 0;
}



void puts(char *str)
{
	while( *str != '\0'){
		putc(*str);
		str++;
	}
	
}

void putc(char byte2send)
{
	while(U1STAbits.UTXBF == 1);
	U1TXREG = byte2send;
}
