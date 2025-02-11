#include <detpic32.h>

int main(void){
	//CONFIGURAR PORTO RB4 COM ENTRADA ANALOGICA, COM 1 CONVERSAO CONSECUTIVA
	TRISBbits.TRISB4=1;		//DESLIGAR DIGITAL OUTPUT
	AD1PCFGbits.PCFG4=0; 		//CONFIGURAR COMO ENTRADA ANALOGICA
	AD1CON1bits.SSRC=7;
	AD1CON1bits.CLRASAM=1;		//CLEAR ASAM
	AD1CON3bits.SAMC=16;
	AD1CON2bits.SMPI=4-1;		//INTERRUPR AFTER N SAMPLES (N-1)
	AD1CHSbits.CH0SA=4;		//SELECIONA CANAL COMO INPUT PARA O A/D CONVERTER
	AD1CON1bits.ON=1;		//LIGA AD CONVERTER(ULTIMA INSTRUÇÃO)

	int aux;
	while(1){
		AD1CON1bits.ASAM=1;		//START CONVERSION
		while(IFS1bits.AD1IF==0);	//WAIT FOR CONVERSION IS DONE
		
		int *p=(int *)(&ADC1BUF0);
		for(;p<=(int *)(&ADC1BUFF); p+=4){
			printInt(*p,10|4<<16);		//Print valor do buffer 4 amostras
							// ADC1BUF0-ADC1BUF4
			aux+=*p;
			putChar(' ');
		}
		int media = aux/4;
		int voltage = ((media*33)+511)/1023;
		printInt(voltage, 10|2<<10);
		putChar('\n');
		IFS1bits.AD1IF=0;		//RESET INTERRUPT FLAG		
		aux=0;		
	}

	return 0;
}
