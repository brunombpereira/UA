#include <detpic32.h>
void delay(int);
void send2displays(unsigned char);
unsigned char toBCD( unsigned char value);
int configUart( unsigned int buad, char parity,unsigned int stopbits);


void delay(int ms) { 
	for(; ms > 0; ms--) { 
		resetCoreTimer(); 
		while(readCoreTimer() < 20000); 
	} 
} 

void setPWM(unsigned int dutyCycle){

	if(dutyCycle<= 100 && dutyCycle>=0){
		OC1RS = ((49999+1) * dutyCycle)/ 100;
	}
}

void putc(char byte2send)
{
	while(U1STAbits.UTXBF == 1);
	U1TXREG = byte2send;
}


volatile unsigned char voltage = 0;		// Global variable
volatile unsigned	char voltmax = 0;
volatile unsigned	char voltmin = 33;

int main(void){
	
	LATDbits.LATD6 = 0;			// display high
	LATDbits.LATD5 = 0;			// display low	
	TRISD = (TRISD & 0xFF9F);
	TRISB = (TRISB & 0x00FF);	// configure RB8 to RB14 and RD5 to RD6 as outputs
	

	// RB4 configuration:

	TRISBbits.TRISB4 	= 1; 	// Digital -> input
	AD1PCFGbits.PCFG4  	= 0; 	// RB4 config as analog input
	AD1CON1bits.SSRC 	= 7; 	// ADC conversion config bits, mode 7
	AD1CON1bits.CLRASAM = 1; 	// conversions be4 interrupt is generated
	AD1CON3bits.SAMC    = 16;	// Sample time is 16 TAD (TAD = 100 ns)
	AD1CON2bits.SMPI	= 7;	// Interrupt is generated after x - 1 samples.
	AD1CHSbits.CH0SA	= 4;	// Desired adc input

	AD1CON1bits.ON		= 1;	// Enable adc (last command)

	// Interupt configuration:	Specific bits in the datasheet

	IPC6bits.AD1IP = 2;		// configure priority of A/D interrupts
	IFS1bits.AD1IF = 0;		// clear A/D interrupt flag
	IEC1bits.AD1IE = 1;		// enable A/D interrupts


	// Timer 3 config
	T3CONbits.TCKPS = 2; 	 // prescaler
	PR3             = 49999; // value to count up to (50000) 
	TMR3            = 0; 	 // Reset timer
	T3CONbits.ON    = 1; 	 // Enable timer

	// Timer 3 interrupt config
	IPC3bits.T3IP = 2;		 // Interrupt priority (must be in range [1..6])
	IEC0bits.T3IE = 1;		 // Enable timer interrupts
	IFS0bits.T3IF = 0;		 // Reset timer interrupt flag

	// T3 pwm config
	OC1CONbits.OCM		= 6;
	OC1CONbits.OCTSEL = 1;		 

	OC1CONbits.ON = 1;


	// Timer 1 config
	T1CONbits.TCKPS = 4; 	 // 1/256 prescaler
	PR1             = 19530; // value to count up to (19531,25) 
	TMR1            = 0; 	 // Reset timer
	T1CONbits.ON    = 1; 	 // Enable timer


	// Timer 1 interrupt config
	IPC1bits.T1IP = 2;		 // Interrupt priority (must be in range [1..6])
	IEC0bits.T1IE = 1;		 // Enable timer interrupts
	IFS0bits.T1IF = 0;		 // Reset timer interrupt flag

	configUart(115200, 'N', 1);

	int dutyCycle;
	int portVal;

	EnableInterrupts();			// Global Interrupt Enable

	while(1){
		portVal = PORTB & 0x0003;

		switch(portVal){
			case 0: 							// Measure input voltage
				IEC0bits.T1IE = 1;  		// Enable T1 interrupts
				setPWM(0); 					// LED OFF
				break;
			case 1: 							// Freeze
				IEC0bits.T1IE = 0;  		// Disable T1 interrupts
				setPWM(100); 				// LED ON (maximum bright)
				break;
			default:							// LED brigthness control
				IEC0bits.T1IE = 1;  		// Enable T1 interrupts
				dutyCycle = voltage * 3;
				setPWM(dutyCycle);
				break;

		}


	}

	return 0;
}

int configUart( unsigned int buad, char parity,unsigned int stopbits){
	int flag=0;	


	if (buad<600 || buad >115200) {

		U1MODEbits.BRGH=0; 					//config baudrate  //taxa transm =16 logo->0
		U1BRG=10;

		flag=1;
	}
	else{
		U1MODEbits.BRGH=0; 					//config baudrate  //taxa transm =16 logo->0
		U1BRG = ((20000000+8*buad) / (16*buad)) - 1;
		LATB = (LATB & 0x00FF) | 7 << 8;
	}

	if (parity != 'E' && parity != 'N' && parity != 'O') {

		U1MODEbits.PDSEL=0;					//paridade: sem paridade

		LATB = (LATB & 0x00FF) | 3 << 8;
		flag=1;
	}
	else{
		//	LATB = (LATB & 0x00FF) | 2 << 8;
		if(parity == 'E' ){
			U1MODEbits.PDSEL = 1;			//paridade: par
		}
		else 	if(parity == 'N' ){
			U1MODEbits.PDSEL = 0;			//paridade: sem paridade
		}
		else 	if(parity == 'O' ){
			U1MODEbits.PDSEL = 2;			//paridade: impar
		}

	}

	if(stopbits != 1 && stopbits !=2){
		U1MODEbits.STSEL=0;					//nº Stop bits=1
		flag=1;
	}
	else{
		U1MODEbits.STSEL = stopbits-1;	//nº Stop bits=stopbits
	}

	
	U1STAbits.UTXEN = 1;						//ativar modulos de transmissao
	U1STAbits.URXEN = 1;						//ativar modulos de recessao

	U1MODEbits.ON = 1;						//ativar UART

	U1STAbits.URXISEL = 0; 					// Enable UART receive interrupt mode

	IPC6bits.U1IP = 2;		 				// Interrupt priority (must be in range [1..6])
	IEC0bits.U1RXIE = 1;				   	// Enable UART interrupts
	IFS0bits.U1RXIF = 0;	 					// Reset UART interrupt flag

	
	return flag;
}


void _int_(24) isr_uart1(void){
	//printStr("ola");
	if(U1RXREG == 'L'){
		
		putc('m');
		char vmin = toBCD(voltmin);
		putc( (vmin >> 4) +'0');					//+'0' é para passar para char
		putc('.');
		putc( (vmin & 0x0F) +'0');	
		putc('\n');


		putc('M');
		char vmax = toBCD(voltmax);
		putc( (vmax >> 4) +'0');					//+'0' é para passar para char
		putc('.');
		putc( (vmax & 0x0F) +'0');	
		putc('\n');
		
		putc('\n');

	}
	IFS0bits.U1RXIF = 0;
}
void _int_(27) isr_adc(void) 				//Replace VECTOR by the A/D
{													//vector number - see "PIC32
	// family datasheet" (pages 74-76)


	int soma=0;
	//nivel=(ADC1BUF0*5)/1024;
	//acesso as 16 posiçoes do buffer
	int *p = (int *)(&ADC1BUF0);
	for(; p <= (int *)(&ADC1BUF7); p+=4 )
	{
		//printInt( *p, 16 | 4 << 16 );
		soma += *p;
		//printf(" ");
	}
	int VAL_AD= soma/8;
	int V=(VAL_AD*33+511)/1023;
	//printf("%d\n", V);
	
	voltage= V;
	
	if(voltage < voltmin) voltmin = voltage;
	if(voltage > voltmax) voltmax = voltage;
	
	IFS1bits.AD1IF = 0;						 //Reset AD1IF flag

}

//rotinas de serviço a interrupção dos timers 
void _int_(4) isr_T1(void) {  
	AD1CON1bits.ASAM = 1;  
	IFS0bits.T1IF = 0;						// Reset T1IF flag       
}   

void _int_(12) isr_T3(void){   
	send2displays(toBCD(voltage));
	static int count = 0;
	if(++count ==100){
		count=0;
		char pc = toBCD(voltage);
		putc( (pc >> 4) +'0');					//+'0' é para passar para char
		putc('.');
		putc( (pc & 0x0F) +'0');	
		putc('\n');
	}
	IFS0bits.T3IF = 0; 						// Reset T3 interrupt flag    
}





















void send2displays(unsigned char value){
	static const char display7Scodes[] ={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
	static int flag=0;
	int hi=value >>4;
	int lo=value & 0x0F;


	//ativa alternadamente(um de cada vez e envia o hi e o lo)
	if(flag!=0)
	{//send digit to high display	

		LATB = (LATB & 0x80FF) | display7Scodes[hi]<<8;
		LATDbits.LATD6=1;
		LATDbits.LATD5=0;
	}
	else
	{
		LATB = (LATB & 0x80FF) | display7Scodes[lo]<<8;
		LATDbits.LATD6=0;
		LATDbits.LATD5=1;
	}
	flag = ~flag;
}

unsigned char toBCD( unsigned char value)
{
	return(((value/10)<<4)| value%10);
}

