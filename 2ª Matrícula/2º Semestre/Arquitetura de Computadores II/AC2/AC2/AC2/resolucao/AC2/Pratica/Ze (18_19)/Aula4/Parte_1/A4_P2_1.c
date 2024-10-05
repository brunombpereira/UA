#include <detpic32.h>

// function declaration:

void delay(int);



int main()
{

	LATE  = 0x000;
	TRISE = (TRISE & 0xFFF0) | 0xFFF0; // Set E port 3-0 as output

	unsigned int i;
	for(i = 0x0000 ; ; )
	{

		LATE = i;

		delay(250);

		i++;

		if(i >= 0x0010) {i = 0x0000;}

	}

	return 0;

}



void delay(int ms)
{
	
	for(; ms > 0; ms--)
		
		{	
			resetCoreTimer();
			while(readCoreTimer() < 20000);
		}

}
