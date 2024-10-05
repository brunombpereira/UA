#include <detpic32.h>

volatile int count = 0;
int main(void){

	T1CONbits.TCKPS = 3;
	PR1 = 39061;
	TMR1 = 0;
	T1CONbits.TON = 1;
	
	//interrupções	T1
	IPC1bits.T1IP = 2;		//prioridade
	IEC0bits.T1IE = 1; 		//Enable T1 interrupts
	IFS0bits.T1IF = 0;		//reset timer T1 interrupt flag
	


	T3CONbits.TCKPS = 5;
	PR3 = 125000;
	TMR3 = 0;
	T3CONbits.TON = 1;
	
	//interrupções	T3
	IPC3bits.T3IP = 2;		//prioridade
	IEC0bits.T3IE = 1; 		//Enable T3 interrupts
	IFS0bits.T3IF = 0;		//reset timer T3 interrupt flag
	
	EnableInterrupts();
	
	while(1);

return 0;
}	

void _int_(12) isr_T3(void){

	putChar('3');	
	IFS0bits.T3IF = 0;
	

}

void _int_(4) isr_T1(void){
	
	putChar('1');	
	IFS0bits.T1IF = 0;
	

}
