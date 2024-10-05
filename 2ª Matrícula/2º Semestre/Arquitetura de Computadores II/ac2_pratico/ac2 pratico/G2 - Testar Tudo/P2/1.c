// 1 Hz -> 1000 ms
// 5Hz -> 200 ms
// 10Hz -> 100 ms

// |       
//    |       |     |     |     |
// |  |   |   |  |  |  |  |  |  |

// devemos considerar o contador com o período menor, pois os outros vão ser múltiplos desses. 
// delay(1Hz) = 10x delay(10Hz), delay(5Hz) = 2 x delay(10Hz)

#include <detpic32.h>

void delay(unsigned int ms);

int main(void)
{
    int cnt1 = 0;
    int cnt5 = 0;
    int cnt10 = 0;

    while(1) // este ciclo é feito a cada 10 ms para verificar todos os restos de divisões
    {
        delay(100);
        cnt10++;                // á partida é que o que vai incrementar primeiramente

    if(cnt10 % 2 == 0){         // só vai ter resto 0 nos instante em que cnt10 for número par,logo 5/10 em cada década.
        cnt5++;
    }
    if(cnt10 % 10 == 0){   
        cnt1++;
    }

    putChar('\r');
    printInt(cnt1,10 | 5 << 16);
    putChar(' ');
    printInt(cnt5,10 | 5 << 16);
    putChar(' ');
    printInt(cnt10,10 | 5 << 16);
    }   
}

void delay(unsigned int ms) 
{ 
 resetCoreTimer(); 
 while(readCoreTimer() < K * ms); 
}