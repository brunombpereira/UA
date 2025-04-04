#include <detpic32.h>
void putc(char byte2send);
void puts(char *str);
int configUart( unsigned int buad, char parity,unsigned int stopbits);
void delay(int ms)
{
	for(; ms > 0; ms--) {
		resetCoreTimer();
		while(readCoreTimer() < 20000);
	}
}

void send2displays(unsigned char value) {
	static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D,  0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
	static char displayFlag = 0;  
	int dh = value >> 4;
	int dl = value & 0x0F;


	if (displayFlag == 0)
	{
		LATDbits.LATD6 = 0;
		LATDbits.LATD5 = 1;
		LATB = (LATB & 0x00FF) | display7Scodes[dl] << 8;
	}else
	{
		LATDbits.LATD6 = 1;
		LATDbits.LATD5 = 0;
		LATB = (LATB & 0x00FF) | display7Scodes[dh] << 8;

	}
	displayFlag = !displayFlag;
}

char getc(void){

	if(U1STAbits.OERR == 1){
		U1STAbits.OERR =0;
	}
	while(U1STAbits.URXDA ==0);
	
	if(U1STAbits.FERR || U1STAbits.PERR){
		int lixo = U1RXREG;
			return 0; 
	}
	else return  U1RXREG;
}


int main(void)
{

	configUart(115200, 'N', 1);
	while(1)
	{
		putc( getc() );
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

int configUart( unsigned int buad, char parity,unsigned int stopbits){
	int flag=0;	


	if (buad<600 || buad >115200) {

		U1MODEbits.BRGH=0; 	//config baudrate  //taxa transm =16 logo->0
		U1BRG=10;

		flag=1;
	}
	else{
		U1MODEbits.BRGH=0; 	//config baudrate  //taxa transm =16 logo->0
		U1BRG = ((20000000+8*buad) / (16*buad)) - 1;
		LATB = (LATB & 0x00FF) | 7 << 8;
	}

	if (parity != 'E' && parity != 'N' && parity != 'O') {

		U1MODEbits.PDSEL=0;		//paridade: sem paridade

		LATB = (LATB & 0x00FF) | 3 << 8;
		flag=1;
	}
	else{
		//	LATB = (LATB & 0x00FF) | 2 << 8;
		if(parity == 'E' ){
			U1MODEbits.PDSEL = 1;		//paridade: par
		}
		else 	if(parity == 'N' ){
			U1MODEbits.PDSEL = 0;		//paridade: sem paridade
		}
		else 	if(parity == 'O' ){
			U1MODEbits.PDSEL = 2;		//paridade: impar
		}

	}

	if(stopbits != 0 && stopbits !=1){
		U1MODEbits.STSEL=0;		//nº Stop bits=1

		flag=1;
	}
	else{
		U1MODEbits.STSEL = stopbits;		//nº Stop bits=stopbits
	}


	U1STAbits.UTXEN = 1;		//ativar modulos de transmissao
	U1STAbits.URXEN = 1;		//ativar modulos de recessao

	U1MODEbits.ON = 1;		//ativar UART


	return flag;
}
