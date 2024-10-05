#include <detpic32.h>


int main(void){
	T3CONbits.TCKPS = 7;
	PR3 = 39061;
	TMR3 = 0;
	T3CONbits.TON = 1;

	IEC0bits.T3IE = 0; 		//disable T3 interrupts
	while(1){
		while(IFS0bits.T3IF == 0){}	//sai qnd acabar 
		putChar('.');
		IFS0bits.T3IF = 0;
	}
return 0;
}	


