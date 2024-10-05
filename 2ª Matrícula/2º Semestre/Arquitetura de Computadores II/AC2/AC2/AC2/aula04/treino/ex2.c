#include <detpic32.h>

int main(void){
	TRISE = TRISE & 0xFF87; 		//1111 1111 1000 0111	
	LATE = LATE & 0xFF87;
	
	int cnt = 0;
	while(1){
		LATE = (LATE & 0xFF87) | (cnt<<3);
		printInt(cnt, 10| 2<<16);
		putChar('\r');
		resetCoreTimer();
		while(readCoreTimer()<20000000*0.25);
		cnt++;
		if(cnt==10){
			cnt = 0;
		}
	}
	return 0;
}
