#include<detpic32.h>
int c;
int x;

volatile int voltage = 0;

unsigned char toBCD(char value);

void send2displays(unsigned char value);

void duty_cycle( int percentagem);

int main(void){
    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB3 = 1;
    PORTBbits.RB0 = 0;
    PORTBbits.RB3 = 0;

    TRISE = TRISE & 0xFF00;
    LATE = LATE & 0xFF00;
    
    TRISDbits.TRISD5 = 0;
    TRISDbits.TRISD6 = 0;
    LATDbits.LATD5 = 0;
    LATDbits.LATD6 = 0;

    TRISB = TRISB & 0x80FF;
    LATB = LATB & 0x80FF;

    TRISBbits.TRISB4 = 1; // RBx digital output disconnected
    AD1PCFGbits.PCFG4= 0; // RBx configured as analog input
    AD1CON1bits.SSRC = 7; // Conversion trigger selection bits: in this
    // mode an internal counter ends sampling and
    // starts conversion
    AD1CON1bits.CLRASAM = 1; // Stop conversions when the 1st A/D converter
    // interrupt is generated. At the same time,
    // hardware clears the ASAM bit
    AD1CON3bits.SAMC = 16; // Sample time is 16 TAD (TAD = 100 ns)
    AD1CON2bits.SMPI = 4-1; // Interrupt is generated after N samples
    // (replace N by the desired number of
    // consecutive samples)
    AD1CHSbits.CH0SA = 4; // replace x by the desired input
    // analog channel (0 to 15)
    AD1CON1bits.ON = 1; // Enable A/D converter
    // This must the last command of the A/D
    // configuration sequenceodule

    U2BRG = (((20000000 + 8*115200)/(16*115200))-1);
    U2MODEbits.BRGH = 0;
    U2MODEbits.PDSEL = 0;
    U2MODEbits.STSEL = 0;
    U2STAbits.UTXEN = 1;
    U2STAbits.URXEN = 1;
    U2MODEbits.ON = 1;

    U2STAbits.URXISEL = 0;

    IEC1bits.U2RXIE = 0;
    IEC1bits.U2TXIE = 0;
    IPC8bits.U2IP = 2;
    IFS1bits.U2RXIF = 0;

    T2CONbits.TCKPS = 2; // 1:32 prescaler (i.e. fout_presc = 625 KHz)
    PR2 = 5000000/100-1; // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz
    TMR2 = 0; // Clear timer T2 count register
    T2CONbits.TON = 1; // Enable timer T2 (must be the last command of the
    // timer configuration sequence)

    IPC2bits.T2IP = 2; // Interrupt priority (must be in range [1..6])
    IEC0bits.T2IE = 1; // Enable timer T2 interrupts
    IFS0bits.T2IF = 0; // Reset timer T2 interrupt flag

    T3CONbits.TCKPS = 0; // 1:32 prescaler (i.e Fout_presc = 625 KHz)
    PR3 = 19999; // Fout = 20MHz / (32 * (62499 + 1)) = 10 Hz
    TMR3 = 0; // Reset timer T2 count register
    T3CONbits.TON = 1; // Enable timer T2 (must be the last command of the
    // timer configuration sequence)


    OC1CONbits.OCM = 6; // PWM mode on OCx; fault pin disabled
    OC1CONbits.OCTSEL = 1;// Use timer T2 as the time base for PWM generation
    duty_cycle(100); // Ton constant
    OC1CONbits.ON = 1; // Enable OC1 module  

    EnableInterrupts();

    
    while(1)
    {
        if((PORTBbits.RB3 == 0) & (PORTBbits.RB0 == 1)){ // MODO RUN
            AD1CON1bits.ASAM = 1;
            while( IFS1bits.AD1IF == 0 );

            int i = 0;
            int media = 0;
            int *p = (int *)(&ADC1BUF0);
            for(;i<4;i++){
                media += p[i*4];
            }

            media = media/4;
            voltage = (media*99+511)/1023;
            duty_cycle(toBCD(voltage));
            LATE = (LATE & 0xFF00) | voltage;
            
            IFS1bits.AD1IF = 0;

            resetCoreTimer();
            while(readCoreTimer() < 20000 * 100 );
        }
        if((PORTBbits.RB3 == 1) & (PORTBbits.RB0 == 0)){ // MODO Comando
        	    IEC1bits.U2RXIE = 1;		//Ativa os interrupts
        	    int scaled = (((c*10)+(x))/2)-8;
        	    printInt(scaled, 10 | 2 << 16);
        	    duty_cycle(scaled);
        	    send2displays(toBCD((char)scaled));
        	    
        	
		
        }
    }
    return 0;
}

void duty_cycle( int percentagem){
    OC1RS = (20000 * percentagem)/100;
}

void _int_(8) isr_T2(void){
    send2displays(toBCD(voltage));
    IFS0bits.T2IF = 0;
}

void send2displays(unsigned char value){

    unsigned const char display7s[] = {0x3F, 0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
    static char displayFlag = 0;
    unsigned char dh = value >> 4;
    unsigned char dl = value & 0x0F;

    if (displayFlag == 0)
    {
        LATD = (LATD & 0xFF9F) | 0x0020; //0000 0000 0010 0000
        LATB = (LATB & 0x80FF);
        LATB = LATB | (display7s[dl] << 8);  //1000 0000 1111 1111
    }
    else
    { //1111 1111 1001 1111
        LATD = (LATD & 0xFF9F) | 0x0040; //0000 0000 0100 0000
        LATB = (LATB & 0x80FF);
        LATB = LATB | (display7s[dh] << 8);  //1000 0000 1111 1111
    }
    displayFlag = ~displayFlag;
}

unsigned char toBCD(char value){
    return ((value/10) << 4) + (value % 10); 
}

void _int_(32) isr_uart2(void){
	int static i = 0;
	if(i==0){
		c = U2RXREG;
		i++;
	}
	else if(i==1){
		x = U2RXREG;
		i++;
	}else{
		i=0;	
	}
	IFS1bits.U2RXIF = 0;
}

 
