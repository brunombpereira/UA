#include <detpic32.h>

volatile unsigned int c = 0;                // valor default do contador

void Config_UART()
{
    U2BRG = 520;                // bps = 2400 
    U2MODEbits.PDSEL =1 ;       // 8 de bits e even parity
    U2MODEbits.STSEL = 1;       // nr de stop bits = 2
    U2STAbits.UTXEN = 1;        // ativar os módulos de transmissão e receção
    U2MODEbits.ON = 1;          // ativar a UART
}

void Config_Interrupts();
{
    U2STAbits.UTXISEL = 0;
    U2STAbits.URXISEL = 0;

    IEC1bits.U2RXIE = 1;        // só queremos interrupções por receção
    IEC1bits.U2TXIE = 0;        // transmissão é feita por polling

    IPC8bits.U2IP = 2;         // prioridade da interrupção

    IFS1bits.U2RXIF = 0;        // interrupt flag apenas da receção

    EnableInterrupts();
}

int main (void)
{
    Config_UART();
    Config_Interrupts();
    TRISE = TRISE & 0xFFF0;                  //RE3..0 como saídas
    LATE = (LATE & 0xFFF0) | c;              //para eles começarem com o valor default

    while(1);
    return 0;
}

void _int_(32) isr_uart2(void)
{ 
    char letra;
    char *str = "VALOR MINIMO\n"; 

    if(IFS1bits.U2RXIF = 1)                  // se a flag de receção estiver a 1 quer dizer que o FIFO pode receber caracteres 
    {                                        // Copy  UxRXREG register to char letra
    letra = U2RXREG;
        if (letra == 'F')
        {
            c++;
            if(c == 10)
            {
                c=0;
            }
        }
        if (letra == 'C')
        {
            c = 0;

            for(;*str != '\0', str++)   //putc do guião, para fazer a transmissão por polling
            {
                while(U2STAbits.UTXBUF = 1);    // esperar enquanto o buffer estiver cheio 
                U2TXREG = *str;
            }
        }
    }
    LATE = (LATE & 0xFFF0) | c;         // convergir o valor do contador
    IFS1bits.U2RXIF = 0;                // voltar a colocar a flag de receção a 0
}