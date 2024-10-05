#include <detpic32.h>
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

	if(stopbits != 1 && stopbits !=2){
		U1MODEbits.STSEL=0;		//nº Stop bits=1

		flag=1;
	}
	else{
		U1MODEbits.STSEL = stopbits-1;		//nº Stop bits=stopbits
	}


	U1STAbits.UTXEN = 1;		//ativar modulos de transmissao
	U1STAbits.URXEN = 1;		//ativar modulos de recessao

	U1MODEbits.ON = 1;		//ativar UART


	return flag;
}

int main(void){
	U1STAbits.URXISEL = 0; //EnableUART receive interrupt mode
	IPC6bits.U1IP = 2; 		//prioridade
	IEC0bits.U1RXIE = 1;
	IFS0bits.U1RXIF = 0;

	configUart(115200, 'N', 1);

	EnableInterrupts();
	while(1);
	return 0;

}

void _int_(24) isr_uart1(void){
	putc(U1RXREG);
	IFS0bits.U1RXIF = 0;
}

