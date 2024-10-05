#include <detpic32.h>
#include "i2c.h"
void i2c1_init(unsigned int clock_freq){

	I2C1BRG= (20000000+ 100000)/(2* 100000)-1; 
	I2C1CONbits.ON= 1;										
}
void i2c1_start(void){
	while((I2C1CON & 0x1F) != 0){};
	I2C1CONbits.SEN = 1;
	while( I2C1CONbits.SEN == 1) ;
}

void i2c1_stop(void){

	while((I2C1CON & 0x1F) != 0){};
	I2C1CONbits.PEN= 1;
	while( I2C1CONbits.PEN == 1) ;

}

int i2c1_send ( unsigned char value){
	I2C1TRN = value;

	while(I2C1STATbits.TRSTAT == 1);
	return I2C1STATbits.ACKSTAT ;
}

char i2c1_receive( char ack_bit ){
	while((I2C1CON & 0x1F) != 0){};
	I2C1CONbits.RCEN = 1;
	while ( I2C1STATbits.RBF == 0){};

	//send ACK bit
	I2C1CONbits.ACKDT = ack_bit &1;
	while((I2C1CON & 0x1F) != 0){};
	I2C1CONbits.ACKEN = 1;
	while(I2C1CONbits.ACKEN==1);

	return I2C1RCV;

}
void delay(unsigned int ms){
	for(; ms>0; ms--){
		resetCoreTimer();
	 	while(readCoreTimer()<20000);
	}
	
}

