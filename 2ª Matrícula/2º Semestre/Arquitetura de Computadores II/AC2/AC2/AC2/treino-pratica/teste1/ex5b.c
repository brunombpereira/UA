#include <detpic32.h>

int main(void){
	int count=0;
	int freq;
	while(1){
		char input = inkey();
		if(input == '0')
		{
			freq = 2*(1+0);
		}
		else if(input == '1')
		{
			freq = 2*(1+1);
		}
		else if(input == '2')
		{
			freq = 2*(1+2);
		}
		else if(input == '3')
		{
			freq = 2*(1+3);
		}
		else if(input == '4')
		{
			freq = 2*(1+4);
		}
		else
		{
			freq=20;
		}
		putChar(input);
		printStr("\n");
		printStr("\r");
		printInt(count, 10|2<<16);
		resetCoreTimer();
		while(readCoreTimer()<20000*freq);
		if(count < 99){
			count++;
		}else count=0;


	return 0;
}
