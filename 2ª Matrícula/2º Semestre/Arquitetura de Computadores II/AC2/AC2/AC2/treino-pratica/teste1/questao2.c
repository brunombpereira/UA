#include <detpic32.h>
void send2display(unsigned char value, int more);

int main(void){
	TRISB = TRISB & 0x80FF;
	LATB = LATB & 0x80FF;
	TRISBbits.TRISB3 = 1;
	TRISD = TRISD & 0xFF9F;
	LATD = LATD & 0xFF9F;

	TRISE = TRISE & 0xFFBD;
	LATE = (LATE & 0xFFBD) | 0x0040;		//0000 0000 0100 0000
	//CONFIGURAR PORTO RB4 COM ENTRADA ANALOGICA, COM 1 CONVERSAO CONSECUTIVA
	TRISBbits.TRISB4=1;		//DESLIGAR DIGITAL OUTPUT
	AD1PCFGbits.PCFG4=0; 		//CONFIGURAR COMO ENTRADA ANALOGICA
	AD1CON1bits.SSRC=7;
	AD1CON1bits.CLRASAM=1;		//CLEAR ASAM
	AD1CON3bits.SAMC=16;
	AD1CON2bits.SMPI=4-1;		//INTERRUPR AFTER N SAMPLES (N-1)
	AD1CHSbits.CH0SA=4;		//SELECIONA CANAL COMO INPUT PARA O A/D CONVERTER
	AD1CON1bits.ON=1;		//LIGA AD CONVERTER(ULTIMA INSTRUÇÃO)

	int aux=0;
	int media;
	char scaled;
	while(1){
		AD1CON1bits.ASAM=1;		//START CONVERSION
		while(IFS1bits.AD1IF==0);	//WAIT FOR CONVERSION IS DONE
		
		int *p=(int *)(&ADC1BUF0);
		for(;p<=(int *)(&ADC1BUFF); p+=4){
			aux+=*p;
		}
		media=aux/4;
		printInt(media, 2 | 12 << 16);
		putChar('\r');
		scaled = (media * 10 / 1023) + 3;
		send2display(scaled, PORTBbits.RB3);
		

		IFS1bits.AD1IF=0;		//RESET INTERRUPT FLAG	
		aux=0;
						//1111 1111 1100 0000
		LATE = LATE ^ 0x0042;		//0000 0000 0100 0010
		resetCoreTimer();
		while(readCoreTimer()<20000000*(1/4));			
	}

	return 0;
}
void send2display(unsigned char value, int more) {
    static const char symbols[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x07F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71 };

    static char digit;

    if(!more) {
        //digit = value >> 4;
        LATD = (LATD & 0xFF9F) | 0x0040;

    } else {
        LATD = (LATD & 0xFF9F) | 0x0020;
        //digit = value & 0x0F;
    }

    digit = symbols[value];

    LATB = (LATB & 0x80FF) | (digit << 8);


}
