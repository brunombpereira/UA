#include <detpic32.h>

int main(void){
	T3CONbits.TCKPS = 7;
	PR3= ((78125/2)-1);
	TMR3=0;
	T3CONbits.TON = 1;
	
	IPC3bits.T3IP = 2;		//interrupt priority
	IEC0bits.T3IE = 1;		//enable t3 interrupts
	IFS0bits.T3IF = 0;		//reset interrupt flag
	
	EnableInterrupts();		//enable interrupts global
	
	while(1);
	return 0;
}


// Rotina de serviço da interrupção
// verificar no data sheet qual o vetor do timer 3

void _int_(12) isr_T3(void){

	putChar('.');
	IFS0bits.T3IF = 0;		// Reset da flag
}
