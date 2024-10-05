#include <detpic32.h>

int main(void){
	TRISE = TRISE & 0xFF03;		 //1111 1111 0000 0011
	LATE = LATE & 0xFF03;

	TRISB = TRISB & 0x0005;			//0000 0000 0000 0101
	PORTB = PORTB & 0x0005;
	
	int aux = 0x00C0; //0000 0000 1100 0000
	int i;
	while(1){
		for(i=0;i<5;i++){
		LATE = (LATE & 0xFF03)|(aux);
		if(PORTB==0x0000){
			resetCoreTimer();
			while(readCoreTimer()<20000000*(1/3.5));
		}else if(PORTB==0x0005){
			resetCoreTimer();
			while(readCoreTimer()<20000000*(1/10.5));
		}
		else{
			resetCoreTimer();
			while(readCoreTimer()<20000000*(1/1));
		}
		aux=aux>>1; 
		}
		LATE = (LATE & 0xFF03);
		aux=0x00C0;
	}
	
	
	return 0;
}
