#include <detpic32.h>

int main(void){
	TRISD = TRISD & 0xFFFA;	//1111 1111 1111 1010
	LATD = LATD & 0xFFFA;
	T3CONbits.TCKPS = 4;
	PR3= 49999;
	TMR3=0;
	T3CONbits.TON = 1;
	
	IPC3bits.T3IP = 2;
	IEC0bits.T3IE = 1;
	IFS0bits.T3IF = 0;
	
	T1CONbits.TCKPS = 6;
	PR1= 62499;
	TMR1=0;
	T1CONbits.TON = 1;
	
	IPC1bits.T1IP = 2;
	IEC0bits.T1IE = 1;
	IFS0bits.T1IF = 0;
	
	EnableInterrupts();
	while(1);
	return 0;
}

void _int_(4) isr_T1(void){
	LATDbits.LATD0=!LATDbits.LATD0;
	IFS0bits.T1IF=0;


}

void _int_(12) isr_T3(void){
	LATDbits.LATD2=!LATDbits.LATD2;
	IFS0bits.T3IF=0;


}
