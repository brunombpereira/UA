//contador com uma frequencia de 5hz usando interrupçoes de T3
// a mostrar nos displays a 200 hz
#include <detpic32.h>
void send2displays(unsigned char value);
unsigned char bin2BCD(unsigned int value);

void configTim(){
T3CONbits.TCKPS = 1;			//kprec=1,52<2
PR3 = 49999;					//10000000/200-1
TMR3 = 0;
T3CONbits.TON = 1;

IPC3bits.T3IP = 2;
IEC0bits.T3IE = 1;
IFS0bits.T3IF = 0;
}

volatile int count=0;
volatile int conta=0;

void _int_(12) isr_T3(void){

	if(count % 40 == 0){//5hz (200/40)
		if(conta ==99){
			conta=0;
		}
		else
			conta++;
	}
	count++;
//	printInt10(conta);
send2displays(bin2BCD(conta));			//200hz
	IFS0bits.T3IF = 0;

}
void _int_(24) isr_adc(void){
	

}
unsigned char bin2BCD(unsigned int value){
	return (((value/10)<<4) + (value%10));

}
volatile int flag=0;

void send2displays(unsigned char value){
	
	static const char array[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D,  0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

	int hd = value >>4;
	int ld = value & 0x0F;
	printInt10(hd);
	if(flag==0){
		LATDbits.LATD6=1;
		LATDbits.LATD5=0;
		TRISB = (TRISB & 0x00FF) |array[hd]<<8;
	}
	else{
		LATDbits.LATD6=0;
		LATDbits.LATD5=1;
		TRISB = (TRISB & 0x00FF) |array[ld]<<8;
	}
	flag= !flag;
}

int main(void){
	TRISB = (TRISB & 0x00FF); 
	TRISDbits.TRISD6=0;
	TRISDbits.TRISD5=0;
	configTim();
	EnableInterrupts();	
	while(1);
return 0;		
}

