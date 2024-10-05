#include <detpic32.h>
unsigned char toBcd(unsigned char value);
void send2displays(unsigned char value);

volatile int voltage=0;

int main(void){
	//CONFIGUrar display
	TRISB = TRISB & 0x80FF;
	LATB = LATB & 0x80FF;
	TRISD = TRISD & 0xFF9F;
	LATD = LATD & 0xFF9F;

	//CONFIGURAR PORTO RB4 COM INTERRUPÇOES
	TRISBbits.TRISB4=1;		//DESLIGAR DIGITAL OUTPUT
	AD1PCFGbits.PCFG4=0; 		//CONFIGURAR COMO ENTRADA ANALOGICA
	AD1CON1bits.SSRC=7;
	AD1CON1bits.CLRASAM=1;		//CLEAR ASAM
	AD1CON3bits.SAMC=16;
	AD1CON2bits.SMPI=8-1;		//INTERRUPR AFTER N SAMPLES (N-1)
	AD1CHSbits.CH0SA=4;		//SELECIONA CANAL COMO INPUT PARA O A/D CONVERTER
	AD1CON1bits.ON=1;		//LIGA AD CONVERTER(ULTIMA INSTRUÇÃO)
	
	IPC6bits.AD1IP = 2;
	IEC1bits.AD1IE = 1;
	IFS1bits.AD1IF = 0;
	
	//CONFIGURAR O TIMER 1 A 5 Hz
	T1CONbits.TCKPS = 2;		//64  
	PR1 = 62499;
	TMR1 = 0;
	T1CONbits.TON = 1;
	
	IPC1bits.T1IP = 2;
	IEC0bits.T1IE = 1;
	IFS0bits.T1IF = 0;
	
	
	//CONFIGURAR O TIMER 3 A 100Hz
	T3CONbits.TCKPS = 2;
	PR3 = 49999;
	TMR3 = 0;
	T3CONbits.TON = 1;
	
	IPC3bits.T3IP = 2;
	IEC0bits.T3IE = 1;
	IFS0bits.T3IF = 0;
	
	IFS1bits.AD1IF=0;
	EnableInterrupts();
	while(1);
	return 0;
}

void _int_(4) isr_T1(void){
	AD1CON1bits.ASAM=1;		//START CONVERSION
	IFS0bits.T1IF=0;		//RESET T1IF FLAG
}	

void _int_(12) isr_T3(void){
	send2displays(toBcd(voltage));
	IFS0bits.T3IF=0;

}

void _int_(27) isr_adc(void){
	int media;
	int aux = 0;
	int *p=(int *)(&ADC1BUF0);
	for(;p<=(int *)(&ADC1BUFF); p+=4){
		aux+=*p;
	}
	media = aux/8;
	voltage = ((media*33)+511)/1023;
	IFS1bits.AD1IF=0;		//RESET INTERRUPT FLAG		
	aux=0;		

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
