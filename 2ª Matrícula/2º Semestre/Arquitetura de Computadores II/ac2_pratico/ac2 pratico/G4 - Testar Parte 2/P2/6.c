#include <detpic32.h>
// o dip switch vai me permitir escolher uma combinação de segmentos de 0 a F
// depois vamos pegar nesse indíce de 0 a F vamos á constante estática usando esse indíce para ativar os segmentos correspondentes

int main(void)
{
    static const char display7Scodes[] = {0x3F, 0x06,0x5b,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x77,0x7C,0x39,0x5E,0x79,0x71};
    int read, code7s;
    
    TRISB = (TRISB & 0x80FF) | 0x000F;  // RB8..14 como saídas,RB3..0
    LATB = LATB & 0x80FF;               // deixar os segmentos todos apagados inicialmente
    TRISD = TRISD & 0xFF9F;             // RD6..5 como saídas
    LATDbits.LATD6 = 0;                 // selecionar o display low, RD5
    LATDbits.LATD5 = 1;

    while(1)
    {
        read = PORTB & 0x000F;          // read dip-switch RB3..0
        code7s = display7Scodes[read];
        LATB = (LATB & 0x80FF) | (code7s << 8);
    }

    return 0;
}