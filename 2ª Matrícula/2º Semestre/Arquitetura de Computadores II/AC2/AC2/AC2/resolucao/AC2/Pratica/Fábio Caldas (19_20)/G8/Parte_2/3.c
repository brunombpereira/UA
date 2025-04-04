#include <detpic32.h>

#define SAMPLES 8
#define fpbclk 20000000

void delay(int ms);
void send2displays(unsigned char value);
unsigned char toBcd(unsigned char value);
void putc(char byte2send);
void putStr(char *str);


void configPorts()
{
	LATB = LATB & 0x80FF;
	TRISB = TRISB & 0x80FF;

	LATD = LATD & 0xFF9F;
	TRISD = TRISD & 0xFF9F;

	//RB0-1 Dip-Switch
	LATB = LATB & 0xFFFC;
	TRISB = TRISB | 0x0003;
}

void configADC()
{
	TRISBbits.TRISB4 = 1;
	AD1PCFGbits.PCFG4 = 0;
	AD1CON1bits.SSRC = 7;
	AD1CON1bits.CLRASAM = 1;
	AD1CON3bits.SAMC = 16;
	AD1CON2bits.SMPI = SAMPLES-1;
	AD1CHSbits.CH0SA = 4;
	AD1CON1bits.ON = 1;

	//IS config
	IPC6bits.AD1IP = 2;	// A/D interrupt priority
	IFS1bits.AD1IF = 0;	// reset A/D interrupt flag
	IEC1bits.AD1IE = 1;	// Enable A/D interrupts
}

void configT1()	// 4Hz
{
	T1CONbits.TCKPS = 3;
	PR1 = 19530;
	TMR1 = 0;
	T1CONbits.TON = 1;

	//T1 interrupt config
	IPC1bits.T1IP = 2;
	IEC0bits.T1IE = 1;
	IFS0bits.T1IF = 0;
}

void configT3() // 100Hz
{
	T3CONbits.TCKPS = 2;
	PR3 = 49999;
	TMR3 = 0;
	T3CONbits.TON = 1;

	//T3 interrupt config
	IPC3bits.T3IP = 2;
	IEC0bits.T3IE = 1;
	IFS0bits.T3IF = 0;
}

void configOC1()
{
	OC1CONbits.OCM = 6;		// PWM mode on OC1
	OC1CONbits.OCTSEL = 1;	// 0 = T2; 1 = T3;
	OC1CONbits.ON = 1;		// Enable OC1 module
}

void setPWM(unsigned int dutyCycle)
{
	if(dutyCycle >= 0 && dutyCycle <= 100)
		OC1RS = ((PR3 + 1)*dutyCycle)/100;
	else
		OC1RS = ((PR3+1)*50)/100;
}

void configUART1(unsigned int baudrate, char parity, unsigned int stopbits)
{
	U1BRG = ((fpbclk+8*baudrate)/(16*baudrate))-1;

	U1MODEbits.BRGH = 0; //divisão por 16

	switch(parity)
	{
		case 'N':
			U1MODEbits.PDSEL = 0; //Sem paridade
			break;

		case 'E':
			U1MODEbits.PDSEL = 1; //Par
			break;

		case 'O':
			U1MODEbits.PDSEL = 2; //Ímpar
			break;

		default:
			U1MODEbits.PDSEL = 0;
			break;
	}

	U1MODEbits.STSEL = stopbits-1;

	U1STAbits.UTXEN = 1; //Transmitter enable
	U1STAbits.URXEN = 1; //Reciever enable

	U1MODEbits.ON = 1; //Enable UART1

	//Interrupt config UART1
	U1STAbits.URXISEL = 0;	//RX interrupt mode

	IPC6bits.U1IP = 2;		//Priority
	IEC0bits.U1RXIE = 1;	//Enable RX
	IFS0bits.U1RXIF = 0;	//Reset RX
}

//Variáveis globais
volatile unsigned char voltage = 0;
volatile unsigned char voltMax = 0;
volatile unsigned char voltMin = 33;

int main(void)
{
	configPorts();
	configADC();
	configT1();
	configT3();
	configOC1();
	configUART1(115200,'N',1);

	int dutyCycle;
	int portVal;

	EnableInterrupts();

	while(1)
	{
		portVal = PORTB & 0x0003;
		switch(portVal)
		{
			case 0:				//Voltimeter and LED_OFF
				IEC0bits.T1IE = 1;
				setPWM(0);
				break;

			case 1:				//Freze and LED_ON(max)
				IEC0bits.T1IE = 0;
				setPWM(100);
				break;

			default:			//LED brightness control
				IEC0bits.T1IE = 1;
				dutyCycle = voltage * 3;
				setPWM(dutyCycle);
				break;
		}
	}

	return 0;
}

void _int_(4) isr_T1(void)
{
	AD1CON1bits.ASAM = 1;
	IFS0bits.T1IF = 0;
}

void _int_(12) isr_T3(void)
{
	static int counter = 0;

	send2displays(voltage);
	if(++counter == 100)
	{
		counter = 0;
		putc(toBcd(voltage >> 4) + '0');
		putc('.');
		putc(toBcd(voltage & 0x0f) + '0');
		putc('\n');
	}
	IFS0bits.T3IF = 0;
}

void _int_(27) isr_adc(void)
{
	int sum = 0;
	int average, v;

	int *value = (int *)(&ADC1BUF0);
	for(; value <= (int *)(&ADC1BUFF); value+=4)
	{
		sum += *value;
	}
	average = sum/SAMPLES;
	v = (average*33)/1023;
	voltage = toBcd(v);

	if(voltage > voltMax)
		voltMax = voltage;
	else if(voltage < voltMin)
		voltMin = voltage;

	IFS1bits.AD1IF = 0;		//Reset AD1IF interrupt flag
}

void _int_(24) isr_uart1(void)
{
	char dummy;
	if(IFS0bits.U1EIF == 1)
	{
		if(U1STAbits.OERR == 1)
			U1STAbits.OERR = 0;
		else
			dummy = U1RXREG;
		IFS0bits.U1EIF = 0;
	}
	if(IFS0bits.U1RXIF == 1)
	{
		if(U1RXREG == 'L')
		{
			putStr("Tensão max: ");
			putc(toBcd(voltMax >> 4) + '0');
			putc('.');
			putc(toBcd(voltMax & 0x0f) + '0');
			putc('\n');
			putStr("Tensão mínima: ");
			putc(toBcd(voltMin >> 4) + '0');
			putc('.');
			putc(toBcd(voltMin & 0x0f) + '0');
			putc('\n');
			putc('\n');
		}
	}
	IFS0bits.U1RXIF = 0;
}

void putc(char byte2send)
{
	while(U1STAbits.UTXBF == 1);
	U1TXREG = byte2send;
}

void putStr(char *str)
{
	while(*str != '\0')
		putc(*str++);
}

void delay(int ms)
{
	for(; ms > 0; ms--)
	{
		resetCoreTimer();
		while(readCoreTimer() < 20000);
	}
}

void send2displays(unsigned char value)
{
	static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
	static char displayFlag = 0;

	unsigned char dl = value & 0x0F;
	unsigned char dh = value >> 4;

	if(displayFlag == 0)
	{
		LATDbits.LATD5 = 1;
		LATDbits.LATD6 = 0;

		LATB = display7Scodes[dl] << 8;

	} else
	{
		LATDbits.LATD5 = 0;
		LATDbits.LATD6 = 1;

		LATB = display7Scodes[dh] << 8;

	}
	displayFlag = !displayFlag;
}

unsigned char toBcd(unsigned char value)
{
	
	return ((value /10) << 4) + (value % 10);
}
