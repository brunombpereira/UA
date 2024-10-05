#include <detpic32.h>

// configuração da UART2
volatile unsigned int c = 15;         // valor máximo por default

void Config_UART()
{
    U2BRG = 130;
    U2MODEbits.PDSEL = 2;           // 8 bits, odd partity
    U2MODEbits.STSEL = 1;           // 2stop bits
    U2STAbits.UTXEN = 1;            // Ativar os módulos de transmissão e receção
    U2STAbits.URXEN = 1;
    U2MODEbits.ON = 1;              // ativar a UART2
}

void Config_Interrupts()
{
    IPC8bits.U2IP = 2;
    
    U2STAbits.UTXISEL = 0;          // interrupt set when output fifo has space for next char; esta linha dá erro for some reason
    U2STAbits.URXISEL = 0;          // interrupt set when input fifo has at least one char

    IEC1bits.U2RXIE = 1;            // interrupções de transmissão desativadas porque assim diz o enunciado, a transmissão é feita por polling
    IEC1bits.U2TXIE = 0;

    IFS1bits.U2RXIF = 0;

    EnableInterrupts();
}

int main(void)
{
    Config_UART();
    Config_Interrupts();
    TRISE = TRISE & 0xFFE1;         // RE4..1 como saídas

    LATE = LATE & 0xFFE1;           // Leds com o valor máximo do contador máximo, por default
    LATE = LATE | (c<<1);

    while(1);
    return 0;
}

void _int_(32) isr_uart2(void)
{
    char letra;
    char *str = "RESET\n"; 

    if (IFS1bits.U2RXIF == 1)       // se flag de interrupção de receção estiver ativa quer dizer que ele não pode receber mais nada e que pode começar a transmitir para libertar espaço
    {
    letra = U2RXREG;                // ler o caracter
        if (letra == 'U')
        {
            c++;
            if ( c == 16)
            c = 0;
        }
        if (letra == 'R')
        {
            c = 0;

            for(; *str != '\0'; str++)
            {
                while(U2STAbits.UTXBF == 1);   // esperar que o circular buffer de transmissão esteja cheio, quando tiver, ele vai só começar a mandar caracteres
                U2TXREG = *str;
            }
        }
    }

    LATE = LATE & 0xFFE1;           // colocar o valor do contador nos leds
    LATE = LATE | (c<<1);

    IFS1bits.U2RXIF == 0;           // reset á IF do módulo de receção
}