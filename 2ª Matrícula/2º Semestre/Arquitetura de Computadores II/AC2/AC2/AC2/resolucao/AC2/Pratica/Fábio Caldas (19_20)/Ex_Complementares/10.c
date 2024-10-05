#include <detpic32.h>

#define SAMPLES 1
#define fpbclk 20000000

// Device-Driver
#define BUS_SIZE 16
#define INDEX_MASK (BUF_SIZE-1)
#define DisableUart1RxInterrupt() IEC0bits.U1RXIE = 0
#define EnableUart1RxInterrupt() IEC0bits.U1RXIE = 1
#define DisableUart1TxInterrupt() IEC0bits.U1TXIE = 0
#define EnableUart1TxInterrupt() IEC0bits.U1TXIE = 1

void comDrv_putc(char byte2send);
void putStr(char *str);
void comDrv_flushRx(void);
void comDrv_flushTx(void);
void comDrv_getc(char *pchar)
void delay(int ms);
void send2displays(unsigned char value);
char toBcd(unsigned char value);

typedef struct
{
	unsigned char data[BUF_SIZE];
	unsigned int head;
	unsigned int tail;
	unsigned int count;
} circularBuffer;

volatile circularBuffer txb;
volatile circularBuffer rxb;

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

void configUART1()
{
	U1BRG = ((fpbclk+8*1200)/(16*1200))-1;
	U1MODEbits.BRGH = 0;	//Div16
	U1MODEbits.PDSEL = 0;	//No parity
	U1MODEbits.STSEL = 0;	//1 stop bit

	U1STAbits.UTXEN = 1;
	U1STAbits.URXEN = 1;
	U1MODEbits.ON = 1;

	U1STAbits.URXISEL = 1;

	IPC6bits.U1IP = 2;
	IEC0bits.U1RXIE = 1;
	IFS0bits.U1RXIF = 0;
}

volatile unsigned int VALadc;

int main(void)
{
	configPorts();
	configADC();
	configT2();
	configUART1();

	EnableInterrupts();

	int input;

	while(1)
	{
		AD1CON1bits.ASAM = 1;
		
		input = PORTB & 0x000F;
		putStr(" RB3:");
		comDrv_putc(((input & 0x08) >> 3)+ '0');
		putStr(" RB2:");
		comDrv_putc(((input & 0x04) >> 2)+ '0');
		putStr(" RB1:");
		comDrv_putc(((input & 0x02) >> 1)+ '0');
		putStr(" RB0:");
		comDrv_putc(((input & 0x01))+ '0');
		
		putChar('\r');
	}

	return 0;
}

void _int_(27) isr_adc(void)
{
	VALadc = ADC1BUF0;

	IFS1bits.AD1IF = 0;
}

void _int_(8) isr_T2(void)
{
	int freq = 1+(VALadc/255);
	send2displays(toBcd(freq));

	IFS0bits.T2IF = 0;
}

void _int_(24) isr_uart1(void)
{
	if(IFS0bits.U1TXIF == 1)
	{
		if(txb.count > 0)
		{
			U1TXREG = txb.data[txb.head];
			txb.head = (txb.head + 1) & INDEX_MASK;
			txb.count--;
		}
		else if(txb.count == 0)
			DisableUart1TxInterrupt();

		IFS0bits.U1TXIF = 0;
	}

	if(IFS0bits.U1RXIF == 1)
	{
		rxb.data[txb.tail] = U1RXREG;
		rxb.tail = (rxb.tail + 1) & INDEX_MASK;
		if(rxb.count < BUF_SIZE)
			rxb.count++;
		else
			rxb.head = (rxb.head + 1) & INDEX_MASK;

		IFS0bits.U1RXIF = 0;
	}
}

void comDrv_putc(char byte2send)
{
	while(txb.count == BUF_SIZE) {}

	txb.data[txb.tail] = byte2send;
	txb.tail = (txb.tail + 1) & INDEX_MASK;

	DisableUart1TxInterrupt();
	txb.count++;
	EnableUart1TxInterrupt();
}

void putStr(char *str)
{
	while(*str != '\0')
	{
		comDrv_putc(*str++);
	}
}

void comDrv_getc(char *pchar)
{
	if(rxb.count == 0)
		return 0;

	DisableUart1RxInterrupt();
	*pchar = rxb.data[rxb.head];
	rxb.count--
	rxb.head = (rxb.head + 1) & INDEX_MASK;
	EnableUart1RxInterrupt();
	return 1;
}

void comDrv_flushRx(void)
{
	rxb.tail = 0;
	rxb.head = 0;
	rxb.count = 0;
}

void comDrv_flushTx(void)
{
	txb.tail = 0;
	txb.head = 0;
	txb.count = 0;
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
