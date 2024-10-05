#include <detpic32.h>
volatile char c;
void putstr(char *s);

int main(void){
// Configurar UART 9600, O, 8, 2

	//UxBRG = (Fpbclk + 8 *baudrate)/(16*baudrate)-1;
	U2BRG = ((20000000 + (8 * 9600))/(16*9600))-1;
	
	U2MODEbits.BRGH = 0;
	
	U2MODEbits.PDSEL = 2;			// 8-bit data, odd parity
	U2MODEbits.STSEL = 1;			// 2 stop bit
	
	U2STAbits.URXEN = 1;			// Receiver Enable bit
	U2STAbits.UTXEN = 1;			// Transmit Enable bit
	
	U2MODEbits.ON = 1;			// Enable UART2
	
//configurar as interrupçoes
	IEC1bits.U2RXIE = 1;			// ENABLE U2RXIE
	IEC1bits.U2TXIE = 0;			// DISABLE U2TXIE
	
	IPC8bits.U2IP = 2;			// SET UART2 PRIORITY LEVEL
	IFS1bits.U2RXIF = 0;			// CLEAR INTERRUPT FLAG

	U2STAbits.URXISEL = 0;			//DEFINE INTERRUPT MODE
	
	EnableInterrupts();			//ENABLE GLOBAL INTERRUPTS
	
//Configurar leds
	TRISE = TRISE & 0xFFE1;		//1111 1111 1110 0001
	LATE = LATE & 0xFFE1;

	int i = 16;
	while(1){
		if(c=='U'){
			LATE = (LATE & 0xFFE1) | (i--<<1);
			if(i==0){
				i=16;
			}
		}
		if(c=='R'){
			putstr("RESET\n");
			c='p';
			i=16;
			LATE = (LATE & 0xFFE1) | 0x001E;
		}
		resetCoreTimer();
		while(readCoreTimer()<20000000);
	
	}
	return 0;
}

void putstr(char *s){
	while (U2STAbits.UTXBF==1);
	while(*s != '\0'){
		U2TXREG= *s++;
	}
}

void _int_(32) isr_uart2(void){
	if(IFS1bits.U2RXIF==1){
		c = U2RXREG;			//READ CHAR FROM FIFO
		IFS1bits.U2RXIF=0;		//RESET INTERRUPT FLAG
	}
}
