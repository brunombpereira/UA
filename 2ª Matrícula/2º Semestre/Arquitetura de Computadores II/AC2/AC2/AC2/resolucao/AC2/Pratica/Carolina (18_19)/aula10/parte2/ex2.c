#include <detpic32.h>
#include "i2c.h"

int getTemperature(int *temperature){
	int ack;
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
		printStr("ERRO");
		i2c1_stop();
	
			return 0;
		}
	//send the Stop event, print an error message and exit loop
	// Receive a value from slave (send NACK as argument); copy
	*temperature = i2c1_receive(I2C_NACK);

	//received value to "temperature" variable
	// Send Stop event
	i2c1_stop();

	return ack;
}

int main(void){
	int temperature;
	int ack;

	while(1)
	{
		ack = getTemperature(&temperature);
		if(ack != 0)
		{
			printStr("error occured reading temperatures");
		}
		printInt10(temperature);
		delay(250);
	}
return 0;
	

}
