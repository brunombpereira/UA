#include <detpic32.h>

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
	IEC1bits.U2RXIE = 1;			// ENABLE U2RXIE
	IEC1bits.U2TXIE = 0;			// DISABLE U2TXIE
	
	IPC8bits.U2IP = 2;			// SET UART2 PRIORITY LEVEL
	IFS1bits.U2RXIF = 0;			// CLEAR INTERRUPT FLAG

	U2STAbits.URXISEL = 0;			//DEFINE INTERRUPT MODE
	
	EnableInterrupts();			//ENABLE GLOBAL INTERRUPTS
	
//Configurar porto RC14
	TRISC = TRISC & 0xBFFF;		//1011 1111 1111 1111
	LATC = LATC & 0xBFFF;
	
	while(1);
	return 0;
}

void _int_(32) isr_uart2(void){
	if(IFS1bits.U2RXIF==1){			//vERIFICAR SE FLAG FOI ATIVADA	
		char c = U2RXREG;
		if(c=='T'){
			LATCbits.LATC14=1;	//LED LIGA
		}
		if(c == 't'){			
			LATCbits.LATC14=0;	//LED DESLIGA
		}
		IFS1bits.U2RXIF=0;		//RESET DA FLAG
	}
}

