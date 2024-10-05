#include <detpic32.h>

int main(void){
	TRISE = TRISE & 0xFF87; //1111 1111 1000 0111
	LATE =  LATE & 0xFF87;
	int count = 0;
	while(1){
		LATE= (LATE & 0xFF87) | count <<3;//Atualizar os porto com o counter (tem de ser colocado na posição desejada)
		printInt(count,10|2<<16);
		resetCoreTimer();
		while(readCoreTimer()<5000000);
		count++;
		if (count == 10){
			count=0;
		}
	}
	return 0;
}
