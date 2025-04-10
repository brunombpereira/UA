#include <detpic32.h>
void putc(char byte);

int main(void){
	//UxBRG = (Fpbclk + 8 *baudrate)/(16*baudrate)-1;
	U2BRG = ((20000000 + (8 * 115200))/(16*115200))-1;
	

	U2MODEbits.BRGH = 0;							//fator de divisão de relógio 16
	U2MODEbits.PDSEL = 0;							//Sem paridade
	U2MODEbits.STSEL = 0;							//1 stop bit

	U2STAbits.UTXEN = 1;							//Transmitter enable
	U2STAbits.URXEN = 1;							//Reciever enable

	IFS1bits.U2RXIF=0;
	IEC1bits.U2RXIE=1;
	IPC8bits.U2IP=2;
	
	U2STAbits.URXISEL=0;

	U2MODEbits.ON = 1;							//Enable UART2
	
	EnableInterrupts();
	
	TRISC = TRISC & 0xBFFF; 		//1011 1111 1111 1111
	LATC = LATC & 0xBFFF;
	
	while(1);

	return 0;
}

void _int_(32) isr_uart2(void){
	if(IFS1bits.U2RXIF==1){
		char input = U2RXREG;
		putc(input);
		if(input=='T'){
			LATC = (LATC & 0xBFFF) | 0x4000;
		}		
		if(input=='t'){
			LATC = (LATC & 0xBFFF) | 0x0000;
		}
		IFS1bits.U2RXIF=0;
	}

}

void putc(char byte){
	while (U2STAbits.UTXBF==1);
	U2TXREG= byte;
}
