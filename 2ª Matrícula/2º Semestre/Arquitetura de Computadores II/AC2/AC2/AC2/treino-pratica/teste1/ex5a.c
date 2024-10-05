#include <detpic32.h>

int main(void){
	int count=0;
	while(1){
		printStr("\r");
		printInt(count, 10|2<<16);
		resetCoreTimer();
		while(readCoreTimer()<20000*100);
		if(count < 99){
			count++;
		}else count=0;

	}


	return 0;
}
