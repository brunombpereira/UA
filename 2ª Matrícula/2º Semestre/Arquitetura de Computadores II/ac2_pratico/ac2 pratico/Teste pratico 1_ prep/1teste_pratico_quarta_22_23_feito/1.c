#include <detpic32.h>
// contador crescente módulo 10, conta de 0 a 9
int main(void)
{
    TRISE = TRISE &  0xFFC3;        //  x x _ _   _ _ x x RE5..RE2 como saídas
    LATE = LATE & 0xFFC3;           // para os LEDS começarem apagados
    TRISB = TRISB | 0x0004;         //  x 1 x x RB2 como entrada, que vai controlar as frequências de atualização do contador

    int cnt = 0;                    // incializar a variável de contagem

    while(1){
        if (PORTBbits.RB2 == 1){
            LATE = (LATE & 0xFFC3) | (cnt <<2);        // convergir as saídas com o valor do contador
            resetCoreTimer();                           // f = 5.2hz
            while (readCoreTimer() < 3846153);
            if(cnt < 9)
            cnt++;
            else
            cnt = 0;
        }
        else if(PORTBbits.RB2 == 0){
            LATE = (LATE & 0xFFC3) | (cnt <<2);        // convergir as saídas com o valor do contador
            resetCoreTimer();                       // f = 2.3hz
            while (readCoreTimer() < 8695652);
            if(cnt < 9)
            cnt++;
            else
            cnt = 0;
        }
    }
}