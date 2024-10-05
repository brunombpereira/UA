#include <detpic32.h>
volatile int count = 0;

int main(void){
	T3CONbits.TCKPS = 7;
	PR3 = 39061;
	TMR3 = 0;
	T3CONbits.TON = 1;
	
	//interrupções
	IPC3bits.T3IP = 2;		//prioridade
	IEC0bits.T3IE = 1; 		//Enable T3 interrupts
	IFS0bits.T3IF = 0;		//reset timer T3 interrupt flag
	
	EnableInterrupts();
	
	while(1);

return 0;
}	

void _int_(12) isr_T3(void){
	if( ++count % 2 == 0){
		putChar('.');	
	}
	IFS0bits.T3IF = 0;
	

}


