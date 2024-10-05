#include <detpic32.h>

int main(void){
	TRISE = TRISE & 0xFFF0;
	LATE = LATE & 0xFFF0;

	while(1){
			char input = getChar();
		switch(input)
			{
				case '0':
					LATEbits.LATE0 = 1;
					break;

				case '1':
					LATEbits.LATE1 = 1;
					break;

				case '2':
					LATEbits.LATE2 = 1;
					break;

				case '3':
					LATEbits.LATE3 = 1;
					break;

				default:
					LATE = LATE | 0x000F;
					resetCoreTimer();
					while(readCoreTimer()<20000*1000);
					LATE = LATE & 0xFFF0;
					break;
		}
	
	}



	return 0;
}
