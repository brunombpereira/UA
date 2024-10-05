#include <detpic32.h>

#define SAMPLES 8
#define fpbclk 20000000

void putc(char byte2send);
void putStr(char *str);
void delay(int ms);
void send2displays(unsigned char value);
char toBcd(unsigned char value);

void configPorts()
{
	//Dip-Switch
	LATB = LATB & 0xFFF0;
	TRISB = TRISB | 0x000F;

	//Display output
	LATB = LATB & 0x00FF;
	TRISB = TRISB & 0x00FF;

	//Display Hi&Lo
	LATD = LATD & 0xFF9F;
	TRISD = TRISD & 0xFF9F;
}

void configADC()
{
	TRISBbits.TRISB4 = 1;
	AD1PCFGbits.PCFG4 = 0;
	AD1CON1bits.SSRC = 7;
	AD1CON1bits.CLRASAM = 1;
	AD1CON3bits.SAMC = 16;
	AD1CON2bits.SMPI = SAMPLES - 1;
	AD1CHSbits.CH0SA = 4;
	AD1CON1bits.ON = 1;

	IPC6bits.AD1IP = 2;
	IEC1bits.AD1IE = 1;
	IFS1bits.AD1IF = 0;
}

void configT2()
{
	T2CONbits.TCKPS = 2;
	PR2 = 49999;
	TMR2 = 0;
	T2CONbits.TON = 1;

	IPC2bits.T2IP = 2;
	IEC0bits.T2IE = 1;
	IFS0bits.T2IF = 0;
}

void configUART1(unsigned int baudrate, char parity, unsigned int stopbits)
{
	U1BRG = ((fpbclk + 8*baudrate)/(16*baudrate))-1;
	U1MODEbits.BRGH = 0;
	switch(parity)
	{
		case 'N':
			U1MODEbits.PDSEL = 0;
			break;

		case 'E':
			U1MODEbits.PDSEL = 1;
			break;

		case 'O':
			U1MODEbits.PDSEL = 2;
			break;
	}
	U1MODEbits.STSEL = stopbits-1;

	U1STAbits.UTXEN = 1;
	U1STAbits.URXEN = 1;
	U1MODEbits.ON = 1;
}

volatile unsigned int VALadc;

int main(void)
{
	configPorts();
	configADC();
	configT2();
	configUART1(1200,'N',1);

	EnableInterrupts();

	int input;

	while(1)
	{
		AD1CON1bits.ASAM = 1;

		input = PORTB & 0x000F;
		putStr("RB3:");
		putc(((input & 0x08) >> 3) + '0');
		putStr(" RB2:");
		putc(((input & 0x04) >> 2) + '0');
		putStr(" RB1:");
		putc(((input & 0x02) >> 1) + '0');
		putStr(" RB0:");
		putc((input & 0x01) + '0');

		putChar('\r');
	}

	return 0;
}

void _int_(27) isr_adc(void)
{
	int sum = 0;

	int *p = (int *)(&ADC1BUF0);
	for(; p <= (int *)(&ADC1BUFF); p += 4)
	{
		sum += *p;
	}
	VALadc = sum / SAMPLES;

	IFS1bits.AD1IF = 0;
}

void _int_(8) isr_T2(void)
{
	int freq = 1+(VALadc/255);
	send2displays(toBcd(freq));

	IFS0bits.T2IF = 0;
}

void putc(char byte2send)
{
	while(U1STAbits.UTXBF == 1);
	U1TXREG = byte2send;
}

void putStr(char *str)
{
	while(*str != '\0')
	{
		putc(*str++);
	}
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

char toBcd(unsigned char value)
{
	
	return ((value / 10) << 4) + (value % 10);
}
