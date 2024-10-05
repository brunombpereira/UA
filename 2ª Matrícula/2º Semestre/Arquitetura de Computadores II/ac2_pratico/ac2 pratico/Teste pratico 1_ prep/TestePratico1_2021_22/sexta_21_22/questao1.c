#include <detpic32.h>
// 000000 ... 110000...001100...000011
int main(void)
{
    TRISE = TRISE & 0xFF03;          // RE7..2 como saídas  _ _ _ _   _ _ x x 
    TRISB = TRISB | 0x0005;          // RB2 e RB0 como entradas, _ 1 _ 1 

    // Se RB2 & RB0 = 1 -> f = 10.5hz
    // Se RB2 & RB0 = 0 -> f = 3.5hz
    // qualquer outra combinação mantém a frequência anterior
    // f. inicial - 10.5hz
    
    int counter = 0xC0;               // 1100 0000, valor inicial que vou fazer convergir com as saídas e ewscuso de fazer o shift, desta
    // forma já estou a colocar os primeiros 2's uns a convergir com o RB7 e o RB6
    int ms = 0;

    while(1)
    {
        LATE = (LATE & 0xFF03) | counter;                       // convergir saídas com o contador
        counter = counter >> 1;                                 // avançar uma posição, 011000
        if (counter == 0x000C)                                  // caso o contador já tenha atingido o valor máximo, damos reset ao valor inicial
            counter = 0x00C0;
            
        if((PORTBbits.RB2 == 1) & (PORTBbits.RB0 == 1))
        {
            ms = 95 ;       // 1/10.5
        }
        else if((PORTBbits.RB2 == 0) && (PORTBbits.RB0 == 0))
        {
            ms = 285;           // 1/3.5
        }
        resetCoreTimer();
        while(readCoreTimer() < 20000*ms);
    }
}
