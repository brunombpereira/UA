#include <detpic32.h>
void putstrInt(char *s);

typedef struct{
	char mem[100]; 			// Storage area
	int nchar; 				// Number of characters to be transmitted
	int posrd; 				// Position of the next character to be transmitted
} t_buf;


volatile t_buf txbuf;

int main(void){
// Configurar UART 114200, N, 8, 1

	//UxBRG = (Fpbclk + 8 *baudrate)/(16*baudrate)-1;
	U2BRG = ((20000000 + (8 * 115200))/(16*115200))-1;
	
	U2MODEbits.BRGH = 0;
	
	U2MODEbits.PDSEL = 0;			// 8-bit data, no parity
	U2MODEbits.STSEL = 0;			// 1 stop bit
	
	U2STAbits.URXEN = 1;			// Receiver Enable bit
	U2STAbits.UTXEN = 1;			// Transmit Enable bit
	
	U2MODEbits.ON = 1;			// Enable UART2
	
//configurar as interrupçoes
	IEC1bits.U2RXIE = 0;			// DISABLE U2RXIE
	IEC1bits.U2TXIE = 0;			// DISABLE U2TXIE
	
	IPC8bits.U2IP = 2;			// SET UART2 PRIORITY LEVEL

	U2STAbits.UTXISEL = 0;			//DEFINE INTERRUPT MODE
	
	EnableInterrupts();			//ENABLE GLOBAL INTERRUPTS
	
	txbuf.nchar = 0;			//INICIALIZE NCHAR WITH 0
	
	while(1){
		putstrInt("Test string which can be as long as you like, up to a maximum of 100\
 characters\n");
	}
	return 0;
}

void _int_(32) isr_uart2(void){
	if(IFS1bits.U2TXIF==1){
		if(txbuf.nchar>0){		//BUFFER NAO ESTA VAZIO
			U2TXREG = txbuf.mem[txbuf.posrd++];
			// READ CHAR FROM ARRAY
			txbuf.nchar--;
			// DECREMENT THE NUMBER OF CHARS
		}else{
			IEC1bits.U2TXIE = 0;			// DISABLE U2TXIE	
		}
		IFS1bits.U2TXIF=0; 		//RESET FLAG
	}
}

void putstrInt(char *s){
	while(txbuf.nchar>0);			//WAIT WHILE BUFFER IS NOT EMPTY
	while(*s != '\0'){			//WHILE *S NOT END OF THE STRING
		txbuf.mem[txbuf.nchar++]=*s++; 
		//VAI GUARDAR NO ARRAY O CARACTER DA STRING
		//INCREMENTA O NUMERO DE CARACTERES DA STRUCT E A POSIÇÃO DO PONTEIRO
	
	}
	txbuf.posrd = 0;			//INICIALIZE WITH 0
	IEC1bits.U2TXIE = 1;			//ENABLE U2TXIE
	

}
