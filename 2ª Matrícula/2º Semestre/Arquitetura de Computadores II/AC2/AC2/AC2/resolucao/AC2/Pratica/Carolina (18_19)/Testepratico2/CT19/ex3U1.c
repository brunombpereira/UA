#include <detpic32.h>
//UART2 ler, atraves de interrupçoes um caracter do teclado e devolver em maiuscusa se fosse minuscula
//e devolver o teu nome se carregar no 'N' se nao, devolver o caracter inserido
void putc(int byte2send){
	while(U1STAbits.UTXBF ==1);
	U1TXREG = byte2send;
}
void puts(char *s){
	while(*s!='\0'){
		putc(*s);
		s++;
	}

}
char getc(void){
	if (U1STAbits.OERR == 1)
		U1STAbits.OERR==0; 
	while(U1STAbits.URXDA ==0);
	return U1RXREG;
}

int main(void){
		U1BRG =10 ;
		U1MODEbits.BRGH =	0; //taxa 16
		U1MODEbits.PDSEL = 0;
		U1MODEbits.STSEL=0;
		U1STAbits.URXEN = 1;
		U1STAbits.UTXEN = 1;

		U1MODEbits.ON =1;
		
		//interrupçoes
		U1STAbits.UTXSEL =0;
		U1STAbits.URXISEL =0;
		
		IPC6bits.U1IP = 2;
		IFS0bits.U1RXIF = 0;
		IEC0bits.U1RXIE = 1;
		EnableInterrupts();
		while(1);
return 0 ;		
}

void _int_(24) isr_Uart1(void){
	int val=getc();
		if (val=='C')
			puts("carolinaPinho");
		else if( val < 0x7A && val > 0x61) {
			putc(val - 0x20);
		}
		else{
			putc(getc());
		}
		
	IFS0bits.U1RXIF = 0;
}

