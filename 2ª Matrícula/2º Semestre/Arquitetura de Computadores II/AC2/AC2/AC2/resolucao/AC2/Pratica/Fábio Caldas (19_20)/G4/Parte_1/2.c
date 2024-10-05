#include <detpic32.h>

void delay(int ms);

void configPorts()
{
	//Cada 'F' representa 4 bits(porque está representado em Hex(0x...)).
	LATE = LATE & 0xFFF0;	//RE0-3 = 0
	TRISE = TRISE & 0xFFF0;	//RE0-3 Outputs
}

int main(void)
{
	configPorts();
	
	unsigned int count = 0;

	while(1)
	{
		LATE = count;
		count++;
		delay(250);
	} 

	return 0;
}

void delay(int ms)
{
	for(; ms > 0; ms--)
	{
		resetCoreTimer();
		while(readCoreTimer() < 20000);
	}
}

/*
um contador crescente, atualizado a uma frequência de 4Hz.
*(os leds têm de piscar 4x por segundo(1000ms))*
O resultado deverá ser observando nos portos RE0 a RE3.


Como o clk funciona a 40Mhz e como o contador é atualizado a cada 2 ciclos, este dá 20M de tiques por cada segundo.
Para obter um atraso de 1ms(1/1000 s), temos de dividir os 20M/20000.
Para um atraso de 1ms, "k" será 20000. (sendo readCoreTimer() < k).
*/