#include <detpic32.h>

int main(void){

//CONFIGURAÇÃO DO TIMER 3 A 25 HZ

// k = ((20000000/(65535+1)*25))= 12,2 = 16
// fout_presc = 20000000/16= 12500000


	T3CONbits.TCKPS = 4;		// 2^4 = 16
	PR3= ((1250000/25)-1);
	TMR3=0;
	T3CONbits.TON = 1;
	
	IPC3bits.T3IP = 2;		//interrupt priority
	IEC0bits.T3IE = 1;		//enable t3 interrupts
	IFS0bits.T3IF = 0;		//reset interrupt flag
	
//CONFIGURAÇÃO DO TIMER 1 A 5HZ

// k = ((20000000/(65535+1)*5))= 61,03 = 64
// Timer um tem constante 1,8,64,256 logo 64 é o tckps 2
// fout_presc = 20000000/64 = 312500
	T1CONbits.TCKPS = 2;
	PR1= ((312500/5)-1);
	TMR1=0;
	T1CONbits.TON = 1;
	
	IPC1bits.T1IP = 2;		//interrupt priority
	IEC0bits.T1IE = 1;		//enable t3 interrupts
	IFS0bits.T1IF = 0;		//reset interrupt flag
		

	EnableInterrupts();		//enable interrupts global
	
	while(1);
	return 0;
}


// Rotina de serviço da interrupção
// verificar no data sheet qual o vetor do timer 3

void _int_(12) isr_T3(void){
	putChar('3');
	IFS0bits.T3IF = 0;		// Reset da flag
}

void _int_(4) isr_T1(void){
	putChar('1');
	IFS0bits.T1IF=0;

}
