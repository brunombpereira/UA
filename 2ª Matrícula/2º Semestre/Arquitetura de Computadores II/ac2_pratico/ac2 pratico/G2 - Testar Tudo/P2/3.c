#include <detpic32.h>

void delay(unsigned int ms);

int main(void)
{
    char c;                      // armazena variáveis até 256
    int cnt1 = 0;
    int cnt5 = 0;
    int cnt10 = 0;

    while(1)
    {
        c = inkey();

        if(c == 'A'){
             delay(50);         // período mais pequeno passa a ser (1/20) * 1000 = 50ms 
             cnt10++;

            if(cnt10 % 2 == 0){         // só vai ter resto 0 nos instante em que cnt10 for número par,logo 5/10 em cada década.
            cnt5++;
            }

            if(cnt10 % 10 == 0){   
            cnt1++;
            }

            putChar('\r');
            printInt(cnt1,10 | 5 << 16);    // base 10 com 5 dígitos
            putChar(' ');
            printInt(cnt5,10 | 5 << 16);
            putChar(' ');
            printInt(cnt10,10 | 5 << 16);

        } 

        else if(c == 'N'){
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