#include <detpic32.h>

int main (void)
{
	U1MODEbits.BRG=0; 	//config baudrate  //taxa transm =16 logo->0
	U1BRG=10;

	U1MODEbits.PDSEL=0;		//paridade: sem paridade
	U1MODEbits.STSEL=0;		//nº Stop bits=1
	
	U1STAbits.UTXEN = 1;		//ativar modulos de transmissao
	U1STAbits.URXEN = 1;		//ativar modulos de recessao

	U1MODEbits.ON = 1;		//ativar UART

}
