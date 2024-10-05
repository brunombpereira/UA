#include <detpic32.h>
unsigned char toBcd(unsigned char value);
void send2displays(unsigned char value);

int main(void){
	//CONFIGUrar display
	TRISB = TRISB & 0x80FF;
	LATB = LATB & 0x80FF;
	TRISD = TRISD & 0xFF9F;
	LATD = LATD & 0xFF9F;

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
	int i = 0;
	int voltage=0;
	int media;
	while(1){
		if(i==0){
			AD1CON1bits.ASAM=1;		//START CONVERSION
			while(IFS1bits.AD1IF==0);	//WAIT FOR CONVERSION IS DONE
			
			int *p=(int *)(&ADC1BUF0);
			for(;p<=(int *)(&ADC1BUFF); p+=4){
				printInt(*p,10|4<<16);		//Print valor do buffer 4 amostras
								// ADC1BUF0-ADC1BUF4
				aux+=*p;
				putChar(' ');
			}
			media = aux/4;
			voltage = ((media*33)+511)/1023;
			printInt(voltage, 10|2<<10);
			putChar('\n');
			IFS1bits.AD1IF=0;		//RESET INTERRUPT FLAG		
			aux=0;		
		}
		send2displays(toBcd(voltage));
		resetCoreTimer();
		while(readCoreTimer()<20000*10);
		i=(i+1)%5;
	}

	return 0;
}
void send2displays(unsigned char value){
	static const char display7Scodes[]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

	static char displayFlag = 0;
	unsigned char dlow = value & 0x0F;
	unsigned char dhigh = value >> 4;

	if(displayFlag == 0){
		LATD = (LATD & 0xFF9F)|0x0020;		// 0000 0000 0010 0000
		LATB = (LATB & 0x80FF)| display7Scodes[dlow] <<8;
	}else{
		LATD = (LATD & 0xFF9F)|0x0040;		// 0000 0000 0100 0000
		LATB = (LATB & 0x80FF)| display7Scodes[dhigh]<<8;
	}
	displayFlag = !displayFlag;

}

unsigned char toBcd(unsigned char value){
	return ((value/10)<<4) + (value%10);
}
