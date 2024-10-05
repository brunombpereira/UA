#include <detpic32.h>

int main(void){
	// 1- começamos pela formula do Kprescaler
	// 	k=((20000000/(65535+1)*fout))
	// 2- calculamos o fout_presc
	//	Fout_presc = 20MHz / k
	// 3- calculamos o PRX
	//	PRX = (fout_presc/Fout_final)-1
	
	
	// ex: queremos um frequencia de saida de 2 hz
	// 	k = ((20000000/(65535+1)*2))= 152,6
	// 	ou seja o k que temos de usar é o 256
	// 	tckps vai ser 7 pois o t3 avança o 128, 2⁷ será 256 no caso
	
	// 	fout_presc = 20MHz/256= 78125
	
	//	PRx=((78125/2)-1



	T3CONbits.TCKPS= 7;		// queremos x (2^x= constante do prescaler)
	PR2 = (78125/2)-1;		//
	TMR3 = 0;			// CLEAR TIMER T3 COUNT
	T3CONbits.TON = 1;		// ENABLE TIMER T3

	while(1){
		while (IFS0bits.T3IF==0);
		IFS0bits.T3IF=0;
		putChar('.');
	}
	return 0;
}
