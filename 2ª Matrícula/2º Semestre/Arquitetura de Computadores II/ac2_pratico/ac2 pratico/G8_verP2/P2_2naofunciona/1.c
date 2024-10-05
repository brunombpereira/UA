#include <detpic32.h>

int main(void)
{
    TRISDbits.TRISD8 = 1;           // RD8/Int1 configurado como entrada
    TRISEbits.TRISE0 = 0;           // RE0 como saída
    LATEbits.LATE0 = 0;

while(1)
{
    if (PORTDbits.RD8 == 0)         // um interruptor premido está com valor lógico 0
    {
        LATEbits.LATE0 = 1;         // acende o LED durante 3 segundos
        resetCoreTimer();
        while (readCoreTimer() < 60000000);
    }
    else
    {
        LATEbits.LATE0 = 0;
    }
}
    return 0;
}
