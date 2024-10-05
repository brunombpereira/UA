#include <detpic32.h>
void i2c1_init(unsigned int clock_freq);
void i2c1_start(void);


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
int main(){
#define	I2C_READ 1
#define  I2C_WRITE 0
#define I2C_NACK 1
#define I2C_ACK 0

#define SENS_ADDRESS  0x4D // device dependent
#define ADDR_WR	((SENS_ADDRESS << 1) | I2C_WRITE)
#define ADDR_RD   ((SENS_ADDRESS << 1) | I2C_READ)
#define TC74_CLK_FREQ 100000
#define RTR 0 // Read temperature command
			int ack, temperature;
			i2c1_init(TC74_CLK_FREQ);
			while(1)
			{
				// Send Start event
				i2c1_start();
				// Send Address + WR (ADDR_WR); copy return value to "ack" variable
				ack = i2c1_send(ADDR_WR);
				// Send Command (RTR); add return value to "ack" variable
				ack += i2c1_send(RTR);
				// Send Start event (again)
				i2c1_start();

				// Send Address + RD (ADDR_RD); add return value to "ack" variable
				ack += i2c1_send(ADDR_RD);

				// Test "ack" variable; if "ack" != 0 then an error has occurred;
				if(ack != 0){
					i2c1_stop();
					printStr("ERRO");
					break;
				}
				//send the Stop event, print an error message and exit loop
				// Receive a value from slave (send NACK as argument); copy
				temperature = i2c1_receive(I2C_NACK);
			
				//received value to "temperature" variable
				// Send Stop event
				i2c1_stop();
				printStr("TEmperatura");
				printInt10(temperature);
				delay(250);
				// Print "temperature" variable (syscall printInt10)
				// Wait 250 ms
			}
return 0;
}



