#include <detpic32.h>

int main(void){
	//UxBRG = (Fpbclk + 8 *baudrate)/(16*baudrate)-1;
	U2BRG = ((20000000 + (8 * 115200))/(16*115200))-1;
	

	U2MODEbits.BRGH = 0;							//fator de divisão de relógio 16
	U2MODEbits.PDSEL = 0;							//Sem paridade
	U2MODEbits.STSEL = 0;							//1 stop bit

	U2STAbits.UTXEN = 0;							//Transmitter enable
	U2STAbits.URXEN = 1;							//Reciever enable

	IFS1bits.U2RXIF=0;
	IEC1bits.U2RXIE=1;
	IPC8bits.U2IP=2;
	
	U2STAbits.URXISEL=0;

	U2MODEbits.ON = 1;							//Enable UART2
	
	EnableInterrupts();

	while(1);

	return 0;
}
