#include <detpic32.h>
void putc(char byte);
void putstrInt(char *s);

typedef struct{
	char mem[100];
	int nchar;
	int posrd;
} t_buf;

volatile t_buf txbuf;
int main(void){
	//UxBRG = (Fpbclk + 8 *baudrate)/(16*baudrate)-1;
	U2BRG = ((20000000 + (8 * 115200))/(16*115200))-1;
	

	U2MODEbits.BRGH = 0;							//fator de divisão de relógio 16
	U2MODEbits.PDSEL = 0;							//Sem paridade
	U2MODEbits.STSEL = 0;							//1 stop bit

	U2STAbits.UTXEN = 1;							//Transmitter enable
	U2STAbits.URXEN = 1;							//Reciever enable

	IFS1bits.U2RXIF=0;
	IEC1bits.U2RXIE=0;
	IPC8bits.U2IP=2;
	
	IFS1bits.U2TXIF=0;
	IEC1bits.U2TXIE=0;
	
	
	U2STAbits.URXISEL=0;
	U2STAbits.UTXISEL=0;

	U2MODEbits.ON = 1;							//Enable UART2
	
	EnableInterrupts();
	
	txbuf.nchar=0;
	
	while(1){
		putstrInt("Test string which can be as long as you like, up to a maximum of 100\
 characters\n");
	}

	return 0;
}

void _int_(32) isr_uart2(void){
	if(IFS1bits.U2TXIF==1){
		if(txbuf.nchar>0){
			U2TXREG = txbuf.mem[txbuf.posrd];
			txbuf.posrd++;
			txbuf.nchar--;
		}else{
			IEC1bits.U2TXIE=0;	
		}
		IFS1bits.U2TXIF=0;
	}

}
void putstrInt(char *s){
	while(txbuf.nchar > 0);
	while(*s!='\0'){
		txbuf.mem[txbuf.nchar++]=*s++;
	}
	txbuf.posrd = 0;
	IEC1bits.U2TXIE=1;
}

void putc(char byte){
	while (U2STAbits.UTXBF==1);
	U2TXREG= byte;
}
