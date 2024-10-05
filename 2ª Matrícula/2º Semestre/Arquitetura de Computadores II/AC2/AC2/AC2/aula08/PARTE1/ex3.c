#include <detpic32.h>

int main(void){
	T3CONbits.TCKPS = 7;
	PR3= ((78125/2)-1);
	TMR3=0;
	T3CONbits.TON = 1;
	
	IPC3bits.T3IP = 2;
	IEC0bits.T3IE = 1;
	IFS0bits.T3IF = 0;
	
	EnableInterrupts();
	while(1);

	return 0;
}

void _int_(12) isr_T3(void){
	static int i = 0;
	if(i==2){
		putChar('.');
		i=0;
	}
	i++;
	IFS0bits.T3IF=0;


}
