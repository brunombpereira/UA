#include <detpic32.h>

int main (void)
{
        TRISE = TRISE & 0xFFC0;     // configurar RE5..0 como saídas _ _ 0 0  0 0 0 0
        LATE = LATE & 0xFFC0;       // Leds começam apagados
        TRISBbits.TRISB2 = 1;       // RB2 configurado como entrada

        int ms = 0, K = 0;
        int cnt = 0x0001;           // valor inicial 000001, a convergir diretamente com as saídas

        while(1)
        {
            LATE = (LATE & 0xFFC0) | cnt;           // atualizar saídas

            if ( PORTBbits.RB2 == 1)                // if (RB2 == 1) , f = 7hz
            {
                ms = 143;
            }
            if ( PORTBbits.RB2 == 0)                // if (RB2 == 0), f = 3hz
            {
                ms = 333;
            }

            K = 20000*ms;
            resetCoreTimer();
            while(readCoreTimer() < K);      

            if (cnt == 0x0020)
            {
                cnt = 0x0001;
            }
            else{
                cnt = cnt << 1;
            }
        }
    
}
