#include <detpic32.h> 
// ativar segmentos especificos correspondentes a cada um dos leds do display

int main(void)
{
    TRISB = TRISB & 0x80FF;             // 1000 0000 1111 1111 como saídas
    TRISD = TRISD & 0xFF9F;             // 1111 1111 1001 1111

    LATB = LATB & 0x80FF;               // Todos os leds a zero no inicio;
    LATD = (LATD & 0xFF9F) | 0x0020;    // 0000 0000 0100 0000 - RD5=1, i.e. "CNTL_DISP_L"=1, e RD6=0 
    
    while(1)
    {
        char a = getChar ();            //  Ler caracter do teclado a cada ciclo

        if(a == 'a' || a == 'A')
        LATB = (LATB & 0x00FF) | 0x0100;

        if(a == 'b' || a == 'B')
        LATB = (LATB & 0x00FF) | 0x0200;

        if(a == 'c' || a == 'C')
        LATB = (LATB & 0x00FF) | 0x0400;

        if(a == 'd' || a == 'D')
        LATB = (LATB & 0x00FF) | 0x0800;

        if(a == 'e' || a == 'E')
        LATB = (LATB & 0x00FF) | 0x1000;

        if(a == 'f' || a == 'F')
        LATB = (LATB & 0x00FF) | 0x2000;

        if(a == 'g' || a == 'G')
        LATB = (LATB & 0x00FF) | 0x4000;
    }

    return 0;
}