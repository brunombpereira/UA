#include <detpic32.h>
void send2displays(unsigned char value);
unsigned char toBcd(unsigned char value);
char scaled;

int main(void){
//Configurar o ADC
	TRISBbits.TRISB4 = 1;	 // RBx digital output disconnected
	AD1PCFGbits.PCFG4= 0;	 // RBx configured as analog input
	AD1CON1bits.SSRC = 7;	// Conversion trigger selection bits: in this
				// mode an internal counter ends sampling and
				// starts conversion
	AD1CON1bits.CLRASAM = 1; // Stop conversions when the 1st A/D converter
				// interrupt is generated. At the same time,
				// hardware clears the ASAM bit
	AD1CON3bits.SAMC = 16; // Sample time is 16 TAD (TAD = 100 ns)
	AD1CON2bits.SMPI = 2-1; // Interrupt is generated after N samples
				// (replace N by the desired number of
				// consecutive samples)
	AD1CHSbits.CH0SA = 4; // replace x by the desired input
				// analog channel (0 to 15)
	AD1CON1bits.ON = 1; // Enable A/D converter
				// This must the last command of the A/D
				// configuration sequence

//Configurar timer 2 a 120Hz com interrupções
	T2CONbits.TCKPS = 2;
	PR2 = (5000000/120)-1;
	TMR2 = 0;
	T2CONbits.TON = 1;
	
	IPC2bits.T2IP = 2;
	IEC0bits.T2IE = 1;
	IFS0bits.T2IF = 0;
	
	EnableInterrupts();
	
//Configurar displays
	TRISB = TRISB & 0x80FF;	//1000 0000 1111 1111
	LATB = LATB & 0x80FF;
	TRISD = TRISD & 0xFF9F; 	//1111 1111 1001 1111
	LATD = LATD & 0xFF9F;
	
	int aux=0;
	int media;
	while(1){
	//3. o fim da conversao da adc deve ser processado por polling
		AD1CON1bits.ASAM=1;		//START CONVERSION
		while(IFS1bits.AD1IF==0);	//WAIT FOR CONVERSION IS DONE
		
		int *p=(int *)(&ADC1BUF0);
		for(;p<=(int *)(&ADC1BUFF); p+=4){
			aux+=*p;
		}
		
		media=aux/2;
		scaled = (media * 50 / 1023) + 15;
		IFS1bits.AD1IF=0;		//RESET INTERRUPT FLAG	
		aux=0;
		
	//2.A frequencia de amostragem da adc deve ser 10 hz, obtida atraves de Core Timer
		resetCoreTimer();
		while(readCoreTimer()<20000000*(1/10));			
	}




	return 0;
}

//5.Refrescamento dos displays deve ser feito por interrupção
void _int_(8) isr_T2(void){
	send2displays(toBcd(scaled));
	IFS0bits.T2IF = 0;
}
l 
unsigned char toBcd(unsigned char value){
	return ((value/10)<<4) + (value%10);
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
