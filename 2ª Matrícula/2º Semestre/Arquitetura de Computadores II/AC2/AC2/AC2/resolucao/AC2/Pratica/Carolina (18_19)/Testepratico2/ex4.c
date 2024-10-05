#include <detpic32.h>

void configUart(void){
	U1BRG = 21;
	U1MODEbits.BRGH = 0;
	U1MODEbits.PDSEL= 2;		//impar
	U1MODEbits.STSEL = 0;
	//ativar modos de transmissao e recessao
	U1STAbits.UTXEN = 1;
	U1STAbits.URXEN = 1;
	//ativar uart
	U1MODEbits.ON=1;	

	//interrupts recessao
	U1STAbits.URXISEL =0;
	//U1STAbits.UTXSEL =0;

	IPC6bits.U1IP = 2;
	IEC0bits.U1RXIE = 1;
	IEC0bits.U1TXIE = 0;
	IFS0bits.U1RXIF = 0;
}

void putc(char ch){
	while(U1STAbits.UTXBF ==1);
	U1TXREG = ch; 
	
}
void puts(char *ch){
	while(*ch != '\0'){
		putc(*ch);
		ch++;
	}
}

int main(void){
	configUart();
	TRISB = TRISB | 0x000F;			//sw como entradas
	EnableInterrupts();
	while(1);
return 0;

}

void _int_(24) isr_uart1(void){
putc('c');
	int sw= PORTB & 0x000F;
	int v = U1RXREG; 
	if(v == 'L'){
		putc( '0' + sw);
	}
	else if(v == 'S'){
		puts("Carolina Pinho");	
	}
	else if( v  == 'Q')
		exit(1);
	IFS0bits.U1RXIF = 0;
	putc(v);
}

