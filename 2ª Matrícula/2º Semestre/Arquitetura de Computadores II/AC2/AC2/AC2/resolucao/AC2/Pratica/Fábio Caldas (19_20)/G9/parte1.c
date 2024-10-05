#include <detpic32.h>

void comDrv_flushRx(void);
void comDrv_flushTx(void);
void comDrv_putc(char ch);
void comDrv_puts(char *str);
char comDrv_getc(char *pchar);
void delay(unsigned int ms);

#define DisableUart1RxInterrupt() IEC0bits.U1RXIE = 0
#define EnableUart1RxInterrupt() IEC0bits.U1RXIE = 1
#define DisableUart1TxInterrupt() IEC0bits.U1TXIE = 0
#define EnableUart1TxInterrupt() IEC0bits.U1TXIE = 1

#define BUF_SIZE 8
#define INDEX_MASK (BUF_SIZE-1)
#define fpbclk 20000000

typedef struct
{
	unsigned char data[BUF_SIZE];
	unsigned int tail;
	unsigned int head;
	unsigned int count;
} circularBuffer;

volatile circularBuffer txb;
volatile circularBuffer rxb;

void config_comDrv(unsigned int baudrate, char parity, unsigned int stopbits)
{
	if(baudrate >= 600 && baudrate <= 115200)
		U1BRG = (fpbclk +8*baudrate)/(16*baudrate)-1; //config BaudRate generator
	else
		U1BRG = (fpbclk +8*115200)/(16*115200)-1;

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

	if(stopbits == 1)
		U1MODEbits.STSEL = 0; //1 stop bit
	else if(stopbits == 2)
		U1MODEbits.STSEL = 1; //2 stop bit
	else
		U1MODEbits.STSEL = 0;


	U1STAbits.UTXEN = 1; //Transmitter enable
	U1STAbits.URXEN = 1; //Reciever enable

	U1MODEbits.ON = 1; //Enable UART1

	//Interrupt config UART1
	U1STAbits.URXISEL = 0;	//RX interrupt mode
	U1STAbits.UTXSEL = 0;	//TX interrupt mode

	IPC6bits.U1IP = 2;		//Priority
	IEC0bits.U1RXIE = 1;	//Enabled RX interrupt
	IFS0bits.U1RXIF = 0;	//Reset RX

	IPC6bits.U1IP = 2;		//Priority -> Ñ é necessário colocar, redundância
	IEC0bits.U1TXIE = 0;	//Disabled TX interrupt
	IFS0bits.U1TXIF = 0;	//Reset TX
}

int main(void)
{
	char ch;

	config_comDrv(115200, 'N', 1);
	comDrv_flushRx();
	comDrv_flushTx();

	EnableInterrupts();

	comDrv_puts("PIC32 UART Device-driver\n");
	while(1)
	{
		if(comDrv_getc(&ch))
		{
			if(ch == 'S')
				comDrv_puts("Puta que pariu que string grande, nossa, é mesmo gigante, grande como o raio, maior que Jesus\n");
			else
				comDrv_putc(ch);
		}
	}

	return 0;
}

void _int_(24) isr_uart1(void)
{
	//Transmissão
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

	//Receção
	if(IFS0bits.U1RXIF == 1)
	{
		rxb.data[rxb.tail] = U1RXREG;
		rxb.tail = (rxb.tail + 1) & INDEX_MASK;
		if(rxb.count < BUF_SIZE)
			rxb.count++;
		else
			rxb.head = (rxb.head + 1) & INDEX_MASK;

		IFS0bits.U1RXIF = 0;
	}
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

void comDrv_putc(char ch)
{
	while(txb.count == BUF_SIZE) {} 			//wait while buffer is full

	txb.data[txb.tail] = ch;					//Copy ch to the trx buffer at position tail
	txb.tail = (txb.tail + 1) & INDEX_MASK;		//Increment "tail" index (mod. BUF_SIZE)
	
	DisableUart1TxInterrupt();					//Begin Critical Section
	txb.count++;
	EnableUart1TxInterrupt();					//End of Criticital Section
}

void comDrv_puts(char *str)
{
	while(*str != '\0')
		comDrv_putc(*str++);
}

char comDrv_getc(char *pchar)
{
	if(rxb.count == 0)
		return 0;

	DisableUart1RxInterrupt();	//Begin of critical section
	*pchar = rxb.data[rxb.head];
	rxb.count--;
	rxb.head = (rxb.head + 1) & INDEX_MASK;
	EnableUart1RxInterrupt();	//End of critical section
	return 1;
}

void delay(unsigned int ms)
{
	for(; ms > 0; ms--)
	{
		resetCoreTimer();
		while(readCoreTimer() > 20000);
	}
}
