#include <detpic32.h>
//UART2 ler, atraves de interrupçoes um caracter do teclado e devolver em maiuscusa se fosse minuscula
//e devolver o teu nome se carregar no 'N' se nao, devolver o caracter inserido
void putc(int byte2send){
	while(U2STAbits.UTXBF ==1);
	U2TXREG = byte2send;
}
void puts(char *s){
	while(*s!='\0'){
		putc(*s);
		s++;
	}

}
char getc(void){
	if (U2STAbits.OERR == 1)
		U2STAbits.OERR==0; 
	while(U2STAbits.URXDA ==0);
	return U2RXREG;
}

int main(void){
		U2BRG =10 ;
		U2MODEbits.BRGH =	0; //taxa 16
		U2MODEbits.PDSEL = 0;
		U2MODEbits.STSEL=0;
		U2STAbits.URXEN = 1;
		U2STAbits.UTXEN = 1;

		U2MODEbits.ON =1;
		
		//interrupçoes
		U2STAbits.UTXSEL =0;
		U2STAbits.URXISEL =0;
		
		IPC8bits.U2IP = 2;
		IFS1bits.U2RXIF = 0;
		IEC1bits.U2RXIE = 1;
		EnableInterrupts();
		while(1);
return 0 ;		
}

void _int_(32) isr_Uart2(void){
	int val=getc();
		if (val=='C')
			puts("carolinaPinho");
		else if( val < 0x7A && val > 0x61) {
			putc(val - 0x20);
		}
		else{
			putc(getc());
		}
		
	IFS1bits.U2RXIF = 0;
}

