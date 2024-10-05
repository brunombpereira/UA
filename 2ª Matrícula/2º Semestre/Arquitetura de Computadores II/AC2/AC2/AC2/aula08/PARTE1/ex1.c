#include <detpic32.h>

int main(void){
	T3CONbits.TCKPS = 7;
	PR3= ((78125/2)-1);
	TMR3=0;
	T3CONbits.TON = 1;
	
	while(1){
		while(IFS0bits.T3IF==0);
		putChar('.');
		IFS0bits.T3IF=0;
	}





	return 0;
}
