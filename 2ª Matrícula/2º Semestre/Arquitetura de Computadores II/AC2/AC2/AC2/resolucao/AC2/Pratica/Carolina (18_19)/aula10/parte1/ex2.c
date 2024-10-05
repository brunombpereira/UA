#include <detpic32.h>

void i2c1_init(unsigned int clock_freq){

	I2C1BRG= (20000000+ 100000)/(2* 100000i)-1; 
	IFS0bits.I2C1= 1;										
}

