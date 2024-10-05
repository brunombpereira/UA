#include <detpic32.h>

int main(void){
// Configurar o porto RE0 controla o LED0
	TRISE = TRISE & 0xFFFE; 		//1111 1111 1111 1110
	LATE = LATE & 0xFFFE;
	
//Configurar o porto RD8 controla o pulsador INT1
	TRISD = TRISD & 0x0100;		//0000 0001 0000 0000
	PORTD = PORTD & 0x0100;
	
//Configurar timer 2

	T2CONbits.TCKPS = 7 ;		// 256
	PR2 =(78125/3)-1 ;
	TMR2 = 0;
	T2CONbits.TON = 1;
	
	IPC2bits.T2IP = 2;
	IEC0Bits.T2IE = 1;
	IFS0bits.T2IF = 0;
	
	INTCONbits.INT1EP = 0;
	
	EnableInterrupts();
	
	while(1);
	return 0;
}


void _int_(8) isr_T2(void){
	
}

void _int_(7) isr_INT1(void){


}
