// dados random aparecer nos 2 displays ao mesmo tempo sempre que clicamos numa tecla
#include <detpic32.h>

typedef unsigned char uchar; 
typedef unsigned int uint;

void init(void){
	//displays como output - 0 || in
	TRISB &=  0X80FF //1000 0000 1111 1111
        TRISDbits.RD6 = 0; //RD6 como output
	TRISDbits.RD5 = 0; //RD5 como output
	
}//init
