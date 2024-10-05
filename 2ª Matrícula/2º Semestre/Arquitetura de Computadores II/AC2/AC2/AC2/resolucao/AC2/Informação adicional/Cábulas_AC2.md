# Comandos

```c
//Compilar o programa, sendo file o nome do ficheiro
pcompile file.c
//Enviar o programa para a PIC
ldpic32 file.hex
//Executar o programa
pterm
```
# Guião #4
## Configurar Portos
* TRIS: Configurar um porto como entrada ou saída.
```c
//Configurar o porto RE2 como entrada
TRISEbits.TRISE2 = 1;
//Configurar o porto RE5 como saída
TRISEbits.TRISE5 = 0;
```
* PORT: Leitura de valores dos portos de entrada.
```c
//Atribui à variável "abc" o valor lido no porto "RE2"(entrada)
abc = PORTEbits.RE2;
```
* LAT: Escrever valores num porto de saída.
```c
//Atribuição do valor '1' ao bit '3' do porto B:
LATBbits.LATB3 = 1;
//Leitura do porto RE2 e a sua escrita no RB5:
LATBbits.LATB5 = PORTEbits.RE2;
//Inversão do valor de um porto de saída:
LATDbits.LATD0 = !LATDbits.LATD0;
```
## Máscaras de bits
Sendo o 'x' a variável e o 'y' a máscara
```c
	x:  10001101								x:  10001101
	y:  01010111								y:  01010111
x & y:  00000101							x | y:  11011111
Masking to 0								Masking to 1
```
### Acesso a um registo tratando-o como uma variável
Configurar os portos RE1 a RE3 como saída e o porto RE0 como entrada:
```c
TRISE = (TRISE & 0xFFF0) | 0x0001;
```
Se se pretenter alterar os portos RE2 e RE3, colocando-os a 1 e 0, respetivamente, sem alterar o valor de RE1, nem qualquer outro:
```c
LATE = (LATE & 0xFFF3) | 0x0008;
```
## Função delay
Como o clk funciona a 40MHz e como contador é atualizado a cada 2 ciclos, este dá 20M de tiques p/ cada segundo. Para obter um atraso de 1ms(1/1000 s), temos de dividir os 20M/20k. Logo, para um atraso de 1ms, 'k' será 20000.
## Shifts
```c
		y = 1010					y = 1010
		x = y << 1				  	x = y >> 1
yields: x = 0100			yields: x = 0101
```
## Informação adicional
1. frequência de refrescamento: frequência com que os displays atualizam;
2. int = 16 bits;	char = 8 bits (1 byte);
# Guião #5 (Conversão A/D)
## Configurar modo de funcionamento para as conversões A/D da PIC
1. <ins>Configurar um dos portos</ins> de I/O do porto B <ins>como entrada analógica</ins> (registos **TRISB** e **AD1PCFG**);
    Esta configuração envolve sempre dois passos:
* Desligar a componente digital da saída:
```c
//RBn digital output disconnected;
TRISBbits.TRISBn = 1;
```
* Configurar o porto como entrada analógica;

```c
//RBn configured as analog input (ANn);
AD1PCFGbits.PCFGn = 0;
```
2. <ins>Configurar o trigger do processo de início de conversão para "auto convert"</ins> (registo **AD1CON1**, bits **SSRC**);

```c
//Conversion trigger selection(bits): internal counter ends sampling and starts conversion;
AD1CON1bits.SSRC = 7;
```
3. <ins>Determinar que o processo de conversão apenas ocorre quando é dada ordem de início de conversão</ins> (registo **AD1CON1**, bits **CLRASAM**);

```c
//Stop conversions when the 1st A/D converter interrupt is generated. At the same time, hardware clears the ASAM bit;
AD1CON1bits.CLRASAM = 1;
```
4. <ins>Configurar a duração do tempo de amostragem</ins> (registo **AD1CON3**, bits **SAMC**);

```c
//Sample time is 16 TAD (TAD = 100 ns);
AD1CON3bits.SAMC = 16;
```
5. <ins>Configurar o número de conversões consecutivas</ins> do mesmo canal (registo **AD1CON2**, bits **SMPI**);
   Esta configuração é efetuada no registo **AD1CON2** nos 4 bits do campo **SMPI**. Os valores possíveis de configuração vão assim de 0000 a 1111 (1 a 16) conversões consecutivas.
```c
//Interrupt is generated after n samples;
AD1CON2bits.SMPI = n-1;

//n samples will be converted and stored in buffer locations ADC1BUF0 to ADC1BUF(n-1);
```
6. <ins>Selecionar a entrada analógica a converter</ins> (registo **AD1CHS**, bits **CH0SA**);
A seleção do canal de entrada é efetuada através dos 4 bits do campo **CH0SA** do registo **AD1CHS**.

```c
//replace n by the desired input analog channel (0 to 15)
AD1CHSbits.CH0SA = n;
```
7. <ins>Ativar o conversor A/D</ins>, este tem de ser sempre o ultimo comando da sequência de configuração

```c
//Enable A/D converter.
AD1CON1bits.ON = 1;
```
## Processo de conversão (Pos-configuração)
1. <ins>Dar ordem de início de conversão</ins> ao conversor A/D (registo **AD1CON1**, bit **ASAM**);
Um processo de conversão só começa quando há uma ordem explícita de início.

```c
//Start conversion
AD1CON1bits.ASAM = 1
```
2. <ins>Esperar que o sinal que indica fim de conversão fique ativo</ins> (registo **IFS1**, bit **AD1IF**);
* Quando o módulo A/D termina uma sequência de conversão gera um pedido de interrupção (ativa o bit **AD1IF** do registo **IFS1**). Este pedido de interrupção pode ou não ter seguimento, dependendo da configuraçao do sistema de interrupções. Se não estiverem a ser usadas interrupções, a deteção do evento de fim de conversão terá quer ser feita por polling, esperando, em ciclo, que o bit **AD1IF** transite do nível lógico 0 para o nível lógico 1:

```c
//Wait while conversion not done
while(IFS1bits.AD1IF == 0);
```
3. <ins>Ler o resultado da conversão</ins> em **SMPI+1** registos **ADC1BUFn**.

```c
//Ex. de leitura de todas as posições do buffer de armazenamento
int *p = (int *)(&ADC1BUF0);
for(; p <= (int *)(&ADC1BUFF); p+=4)
    {
        printInt(*p, 10 | 4 << 10); //decimal com 4 dígitos
    }
```
* O bit **AD1IF** é automaticamente ativado pelo módulo A/D, mas a sua desativação é manual. Assim, terminada a operação de leitura dos valores da sequência de conversão, é sempre necessário fazer o reset desse bit.

```c
//TEM DE FICAR SEMPRE NO FIM DO CÓDIGO
//Reset do bit AD1IF (responsável pela sinalização do fim da conversão)
IFS1bits.AD1IF = 0
```
## Informação adicional
* Utilizando o system call **printInt()**, imprima o resultado de qualquer coisa (disponível em **wtv**) em hexadeximal, formatado com 3 dígitos:

```c
printInt(wtv, 16 | 3 << 16);
```

* Utilizando o system call **printInt()**, imprima o resultado de qualquer coisa (disponível em **wtv**) em decimal, formatado com 4 dígitos:

```c
printInt(wtv, 10 | 4 << 16);
```

* Os endereços dos 16 registos do buffer de armazenamento dos resultados são múltiplos de 16 (0xBF809070, 0xBF809080, ..., 0xBF809160).

# Guião #6 (Sistema de interrupção)
Quando o módulo A/D termina uma sequeência de conversão gera um pedido de interrupção (ativa o bit **AD1IF** do registo **IFS1**) e para que este pedido tenha um seguimento, o sistema de interrupção do microcontrolador terá que estar devidamente configurado.
## Configuração do sistema de interrupções
1. <ins>Configurar o nível de prioridade</ins> das interrupções geradas pelo módulo A/D (registo **IPC6**¹, nos 3 bits **AD1IP**). Terá que ser escrito <ins>um valor entre 1 e 6</ins>(o valor 7 nunca deve ser usado e para o valor 0 os pedidos de interrupção nunca são aceites, equivalente a estar desativa essa fonte de interrupção (min -> max))

```c
//configure priority of A/D interrupts
IPC6bits.AD1IP = 2; 
```
⁽¹⁾Informação relativa a cada fonte de interrupção está condensada na tabela das páginas 74 a 76 do PIC32MX5XX/6XX/7XX

2. Fazer o <ins>reset de alguma interrupção pendente</ins> (registo **IFS1**, bit **AD1IF**)

```c
//clear A/D interrupt flag
IFS1bits.AD1IF = 0;
```
3. <ins>Autorizar as interrupções geradas</ins> pelo módulo A/D (regist **IEC1**, bit **AD1IE**)

```c
//Enable A/D interrupts
IEC1bits.AD1IE = 1;
```
4. <ins>Ativar</ins> globalmente o <ins>sistema de interrupções</ins>

```c
//Global Interrupt Enable
EnableInterrupts();
```
## Rotina de serviço à interrupção (ISR)
O prefixo "_int_(vector)" indica ao compilador que se trata de uma função de serviço a uma interrupção.

```c
void _int_(VECTOR) isr_adc(void)
{
	//ISR actions
	(...)
	IFS1bits.AD1IF = 0
}

//Replace VECTOR by the A/D vector number
//Available in PIC32MX5XX/6XX/7XX pag. 74 - 76
```
## Informação adicional
**Volatile** - dá a indicação ao compilador que a variável pode ser alterada de forma não explicitada na zona de código onde está a ser usada. Isto obriga o compilador a, sempre que o valor da variável seja necessário, efetuar o acesso àposição de memória onde essa variável reside.

# Guião #7 (Timers)
## Configuração do timer

A programação dos timers envolve 3 passos:
1. Configuração da constate de divisão do prescaler(**TxCON**, bits **TCKPS**);
* Há 5 timers disponíveis, T1-> T5, sendo T1 do tipo A e T2-> T5 do tipo B.
Tipo A: $K_{value}(K)$ = 1(0), 8(1), 64(2), 256(3).
Tipo B:  $K_{value}(K)$= 1(0), 2(1), 4(2), 8(3), 16(4), 32(5), 64(6), 256(7).
Timers T2 e T3 são responsáveis pela base de tempo para a geração dos sinais PWM

```c
TxCONbits.TCKPS = K; //Constate de divisão do prescaler
```
* A configuração deste K vai servir para baixar a frequência à entrada do contador do timer pelo que $ fout = \frac{fout_{prescaler}}{PRx+1} $, sendo que $fout_{prescaler} = \frac {f_{pbclk}}{K_{value}}$, ($f_{pbclk}$= 20MHz).

* Para <ins>determinar o valor mínimo que K</ins> pode tomar, vamos <ins>utilizar o $PRx_{max}$</ins> (2¹⁶-1=65535),

  $K_{value}=\frac{f_{pbclk}}{(PRx_{max}+1)*fout} \iff$ (Para um $fout$ qlq, seja 10Hz), ($K_{value}$ arredonda para cima)

  $K_{value}=\frac{20*10⁶}{(65535+1)*10} =30,51 \sim 31$
  
  K deve de tomar os valores 5(32), 6(64) ou 7(256).
2. Configuração da constante de divisão **PRx**;

```c
PRx = K; //Constate de 16 bits armazenada num dos registos PR1 a PR5 (Timers T1 a T5)
```
* Para configurar **PRx** temos de <ins>saber a frequência $f_{out}$</ins> que pretendemos.

  Supondo que queremos um sinal do timer gerado à frequência de 10Hz,

  $PRx = \frac{fout_{prescaler}}{fout}-1 \iff PRx=\frac{\frac{f_{pbclk}}{K_{value}}}{10}-1 \iff PRx = \frac{20*10⁶}{10*K_{value}}-1$ 

3. Ativação do timer (registo **TxCON**, bit **TON**);

```c
TMRx = 0;				//Reset timer Tx count register
TxCONbits.TON = 1;		//Enable timer Tx
						//(Must be the last command)
```
## Configuração do timer para gerar interrupções
Para utilizar os <ins>timers como geradores de  interrupções</ins> é necessário ainda configurar o sistema de interrupções respeitante aos timers:

```c
IPCxbits.TxIP = 2; 	//Interrupt priority
IEC0bits.TxIE = 1; 	//Enable timer Tx interrupts
IFS0bits.TxIF = 0; 	//Reset timer Tx interrupt flag
EnableInterrupts();	//OU DisableInterrupts();
```
## Geração de um sinal PWM(Pulse Width Modulation)
Esta técninca permite, mantendo o período T, alterar dinamicamente a duração a 1, $t_{on}$, do sinal. O Duty-Cycle é dado por $Duty-cycle = \frac{t_{on}}{T}*100$[%].
No PIC32 a geração de sinais PWM é feita usando os timers T2 ou T3 e o Output Compare Module (OC). Um dos timers T2 ou T3 funciona como base de tempo, isto é, define o período T do sinal, enquanto que o módulo OC permite configurar através do registo **OCxRS**, a duração a 1 desse sinal, isto é, o tempo $t_{on}$.
* Calcular **OCxRS**:
  $OCxRS = \frac{t_{on}}{Tout_{presc}}$
* Calcular **OCxRS** alternativamente, poderemos multiplicar o valor de (**PRx** + 1) pelo valor do duty-cycle pretendido:
  $OCxRS = \frac{(PRx+1)*duty-cycle}{100}$
* Sequência completa de programação para obter o sinal de 10Hz e duty-cycle de 20% na saída OC1:

```c
T2CONbits.TCKPS = 5;	//1:32 prescaler => 625KHz
PR2 = 62499;			// P/ um fout de 10Hz
TMR2 = 0;				//Reset timer T2 count register
T2CONbits.TON = 1;		//Enable timer T2

OC1CONbits.OCM = 6;		//PWM mode on OCx; fault pin disabled
OC1CONbits.OCTSEL = 0;	//Use timer T2 as the time base for PWM generation
OC1RS = 12500;			//Ton constant
OC1CONbits.ON = 1;		//Enable OC1 module
```
O valor do registo OC1RS pode ser modificado em qualquer altura.
As saídas OC1 a OC5estão fisicamente multiplexadas com os bits RD0 a RD4 pelo que a sua configuração como saída é feita automaticamente pelo Output Compare Module **OCx**.

# Guião #8 (UART)
A UART é constituída por 3 módulos fundamentais: módulo de transmissão (TX), módulo de receção(RX) e um gerador de sinal de relógio(baudrate - BRG).
## Módulo de transmissão
* O bloco base é um shift register que faz a conversão paralelo-série, enviando sucessivamente para a linha série os carateres armazenados no buffer de transmissão (buffer FIFO). O envio de informação é feito escrevendo, sucessivamente, os carateres a transmitir no registo **UxTREG** que são copiados para o shift-register de transmissão.
* CLK - obtido através da divisão por 4 ou 16(bit **BRGH** do registo **UxMODE**) do relógio gerado pelo módulo BRG.
* Ativação - feita através do bit **UTXEN** do registo **UxSTA**.
Após reset ou power-on todas as UARTs estão desligadas.
## Módulo de recessão
* Todo o módulo funciona de forma muito idêntica ao módulo de transmissão à exceção de que os sucessivos carateres recebidos pela linha de série são colocados no buffer de receção (FIFO de 8 posições). A gestão destes dados é feita através do registo **UxRXREG**
* CLK - Este relógio é o mesmo que é usado no modulo de transmissão e é obtido através de uma divisão por 4 ou 16(bit **BRGH** do registo **UxMODE**) do relógio gerado pelo módulo BRG
* Ativação - feita através do bit **URXEN** do registo **UxSTA**.
Após reset ou power-on todas as UARTs estão desligadas.
## Gerador de baudrate
* A frequência à saida deste módulo é dada por $f_{BRG}=\frac{f_{pbclk}}{UxBRG + 1}$. 

  O sinal à saída do módulo é depois dividido por 4 ou 16 dependendo da configuração do bit **BRGH** do registo **UxMODE** representando o baudrate(taxa de transmissão/receção da UARTx).

* Para **BRGH(UxMODE<3>)** configurado a 0, vai dividir por 16,

  $baudrate = \frac{f_{pblck}}{16*(UxBRG + 1)}$
* Para **BRGH(UxMODE<3>)** configurado a 1, vai dividir por 4,

  $baudrate = \frac{f_{pblck}}{4*(UxBRG + 1)}$
  OU
  **UxBRG**=$\frac{f_{pbclk}+8*baudrate}{(16*baudrate)}- 1$

* O módulo BRG é comum ao módulo de transmissão e receção pelo que a taxa de transmissão é igual à taxa de receção.
## Configuração da UART
1. Configurar o gerador de baudrate(registo **UxBRG** e bit **BRGH** do registo **UxMODE**).

```c
U1BRG = (fpbclk + 8*baudrate)/(16*baudrate)-1;
```
2. Configurar os parâmetros da trama: dimensão da palavra a transmitir(número de data bits) e tipo de paridade(bits **PDSEL<1:0>** do registo **UxMODE**); número de stop bits (bit **STSEL** do registo **UxMODE**).

```c
U1MODEbits.BRGH = 0;  //(0)Divisão P/16;(1)Divisão P/4
U1MODEbits.PDSEL = 0; //(0)Sem paridade;(1)Even;(2)Odd
U1MODEbits.STSEL = 0; //1 stop bits
```
3. Ativar os módulos de transmissão e receção(bits **UTXEN** e **URXEN** do registo **UxSTA**).

```c
U1STAbits.UTXEN = 1;	//Transmitter enable
U1STAbits.URXEN = 1;	//Reciever enable
```
4. Ativar a **UART**(bit **ON** do registo **UxMODE**).

```c
U1MODEbits.ON = 1;
```
A ativação da UARTx e dos correspondentes módulos de transmissão e receção configura automáticamente o porto de transmissão(**UxTX**) como saída e o porto de receção(**UxRX**) como entrada.

## Procedimento de transmissão - polling
* Verificação do bit **UTXBF** (Transmit Buffer Full) do registo **UxSTA** que quando ativo sinaliza que o FIFO está cheio, pelo que é necessário esperar que o bit **UTXBF** fique inativo para colocar nova informação no FIFO.

```c
void putc(char byte2send)
{
	while(U1STAbits.UTXBF == 1);
	U1TXREG = byte2send;
}
```
## Procedimento de receção - polling
* Verificação do bit **URXDA** (Recieve Data Available) do registo **UxSTA** que quando ativo sinaliza que o FIFO está disponível para ler pelo menos 1 carater, pelo que é necessário esperar que o bit **URXDA** fiquei ativo para proceder à leitura do carater recebido.

```c
char getc(void)
{
	while(U1STAbits.URXDA);
	return U1RXREG;
}
```
É gerado um erro de overrun sinalizado pelo bit **OERR** do registo **UxSTA** sempre que é lido um carater quando o FIFO da receção está cheio e enquanto que não for feito o reset deste bit, a UART não recebe mais nenhum carater. Dessa forma, a função de receção deve incluir o teste à flag **OERR** de modo a efetuar o reset no caso de ocorrência de erro de overrun.

```c
char getc(void)
{
	char clear;
    //erro de overrun
    if(U1STAbits.OERR == 1)
        U1STAbits.OERR = 0;
    while(U1STAbits.URXDA == 0);
    
    //erro de framing   erro de paridade
    if(U1STAbits.FERR || U1STAbits.PERR)
    {
        clear = U1RXREG;
        return 0;
    } else
        return U1RXREG;
}
```
## Configuração da UART com interrupções
O modo como as interrupções são geradas é configurável nos bits **UTXISEL<1:0>** e **URXISEL<1:0>** do registo **UxSTA**. Configurando estes bits como "00" são geradas interrupções nas seguintes situações:
* <ins>Receção</ins>: uma interrupção é gerada quando o FIFO de receção tem, pelo menos, um novo carater para ser lido(a isr pode efetuar a respetiva leitura do registo **UxRXREG**);

```c
//Enable receive(RX) interrupt mode
U1STAbits.URXISEL = 0;
```
* <ins>Transmissão</ins>: uma interrupção é gerada quando o FIFO de transmissão tem, pelo menos, uma posição livre(a isr pode colocar no registo **UxTXREG** um novo carater para ser transmitido);

```c
//Enable transmitter(TX) interrupt mode
U1STAbits.UTXSEL = 0;
```

É necessário ainda configurar os bits de enable das interrupções e os bits que definem a prioridade:

* **UxRXIE**(receive interrupt enable) e **UxTXIE**(transmit interrupt enable) para ativar os interrupts de receção e transmissão;

```c
//Enable interrupts
IEC0bits.U1RXIE = 1;
// E/OU
IEC0bits.U1TXIE = 1;
```
* Os 2 bits **UxIP** para a definição de prioridades;

```c
IPC6bits.U1IP = 2; 	//Interrupt priority
IFS0bits.U1RXIF = 0;//Reset reciever UART interrupt flag 
```

A UART pode ainda gerar interrupções na situação de erro quando é lido um carater(erro de paridade, framing e de overrun) e é também necessário ativar essa fonte de interrupção se se precisar de fazer a deteção desses erros(**UxEIE**).
  **NOTA**: a cada UART está atribuído um único vetor para as 3 possíveis fontes de interrupção pelo que é necessário identificar a fonte de interrupção na isr. Esta identificação é feita através do teste das interrupt flag bits de cada uma das três fontes de interrupção, **UxRXIF**, **UxTXIF**, **UxEIF**.

```c
if(IFS0bits.U1EIF==1)
{
	//Verificar flags dos erros
}

if(IFS0bits.U1RXIF == 1)
{
	//...
}
```
# Guião #9 (Device-driver)
Um device-driver é um programa que permite a uma aplicação comunicar com um dispositivo hardware. Este lida com as especificidades de implementação, configuração e funcionamento do dispositivo e fornece uma interface genérica a partir da qual a aplicação interage com o hardware. um device-driver utiliza interrupções como modelo de transferência de informação.
No caso de um device-driver para a UART a aplicação interage exclusivamente com os FIFOs (que podem ser implementados como buffers circulares) através de funções de leitura e escrita e recorre às interrupções para transferir a informação entre os FIFOs e a UART(responsabilidade do device-driver).
## Transmissão
A função **comDrv_putc()** escreve a informação a enviar para a UART no buffer e mantém atualizadas duas varáives de gestão desse buffer: **tail** e **count**.
* **Tail**: indica a posição de escrita do próximo carater;
* **Count**: indica o número de carateres do buffer;
Estas variáveis são incrementadas (em módulo **n**, sendo **n** a dimensão do buffer) por cada novo carater escrito no buffer.
A informação colocada no buffer circular é enviada por interrupções para a UART(remove)(a isr lê o carater da posição **head** do buffer e escreve-o no registo de transmissão da UART) e as variáveis **head** e **count** são atualizadas, a variável **count** é decrementada e a variável **head** é incrementada em módulo **n**.
## Receção
Sempre que a UART recebe um novo carater gera uma interrupçãoe e na respetiva isr esse carater é copiado para o buffer de receção, para a variável **tail**(append) e são atualizadas as variáveis **tail** e **count**. Estes carateres são lidos pela aplicação(remove) através da função **comDrv_getc()** que, cada vez que lê um carater, atualiza também as variáveis **head** e **count**.
## Implementação dos buffers circulares
Os buffers de tx e rx têm uma estrutura semelhante. Para a implementação de cada um destes buffers é necessário ter uma área de armazenamento e um conjunto de variáveis auxiliares de gestão:
* **tail**: o índice do array onde se pode escrever o próximo carater;
* **head**: o índice do array onde se pode ler um carater;
* **count**: um contador que mantém atualizado o número efetivo de carateres do buffer;

```c
#define BUF_SIZE	32
#define INDEX_MAX	(BUF_SIZE - 1)

//Definição da estrutura do buffer
typedef struct
{
	unsigned char data[BUF_SIZE];
	unsigned int tail;
	unsigned int head;
	unsigned int count;
} circularBuffer;

//A partir desta estrutura podem ser instanciados os dois buffers circulares
volatile circularBuffer txb;	//Transmission buffer
volatile circularBuffer rxb;	//Reception buffer
```
A dimensão do array de carateres (**BUF_SIZE**) deverá ser ajustado em função das necessidade e deve ser um valor que seja uma potência de 2 ($2^n$). A aplicação de uma máscara com o valor da dimensão do array menos 1 (**BUF_SIZE - 1**) após uma operação de incremento, garante a rotação do valor do índice.
## Receção - ISR
Quando a UART gera uma interrupção:
* o carater recebido deve ser transferido para a posição **tail** do buffer de receção;

* o valor de **count** deve ser incrementado e o **tail** deve ser incrementado em módulo **n**.

Se o buffer fica cheio:

* Para não perder a informação mais recente, descarta-se o carater mais antigo incrementando o **head**, sem incrementar o **count**;

## Receção - leitura do buffer

Na função **comDrv_getc()**:

* Ler um carater do buffer de receção, da posição **head**;
* Atualizar as variáveis **count** e **head**;

Como as variáveis **count** e **head** podem ser alteradas na rotina de interrupção e na função **comDrv_getc()** tem de ser escrita uma zona de código (secção **crítica**) onde não é permitido o atendimento de interrupções de receção da UART.  Assim, a interrupção de receção deve ser desativada antes da secção crítica e reativada logo depois.

## Transmissão - escrita no buffer

Na função **comDrv_putc()**:

* copiar o carater a enviar para o buffer;
* atualizar as variáveis **count** e **tail**;

A variável **count** pode também ser escrita na isr, pelo que o código de alteração desta variável fora dessa rotina constitui uma secção crítica.

## Transmissão - ISR

Na UART é gerada uma interrupção enquanto o FIFO de transmissão tem, pelo menos, uma posição livre. Na estrutura do device-driver:

* a isr lê do buffer de transmissão o carater que está em **head** e escreve-o no registo de transmissão da UART.
* Atualiza as variáveis **head** e **count** do buffer
* Quando a variável **count** atinge o valor 0, deve também desativar as interrupções de transmissão da UART (a ativação é efetuada na função **comDrv_putc()** sempre que se colocar um carater no buffer).
## Informação adicional
Rotina da UART melhorada:
1)copia para a UART1 todos os carateres do buffer de transmissão ou copiar até o FIFO ficar cheio;
2)copia para o buffer de receção, até ao limite de espaço disponível, todos os carateres disponíveis no FIFO de receção.

```c
void _int_(24) isr_uart1(void)
{
	//Transmissão
	if(IFS0bits.U1TXIF == 1)
	{
		while(txb.count > 0 && U1STAbits.UTXBF == 0)
		{
			U1TXREG = txb.data[txb.head];
			txb.head = (txb.head + 1) & INDEX_MASK;
			txb.count--;
		}
		if(txb.count == 0)
			DisableUart1TxInterrupt();

		IFS0bits.U1TXIF = 0;
	}

	//Receção
	if(IFS0bits.U1RXIF == 1)
	{
		while(rxb.count < BUF_SIZE && U1STAbits.URXDA != 0)
		rxb.data[rxb.tail] = U1RXREG;
		rxb.tail = (rxb.tail + 1) & INDEX_MASK;
		rxb.count++;

		IFS0bits.U1RXIF = 0;
	}		
}
```
Deteção de erros de overrun, framming, paridade:

```c
//Acrescenta um campo à estrutura do buffer ciruclar
typedef struct
{
    ...
    unsigned int overrun;
} circularBuffer;

...

void _int_(24) isr_uart1(void)
{
	...
	
	if(IFS0bits.U1EIF == 1) //U1EIF - Sinaliza se ocorre algum erro
	{
		char clear;
		if(U1STAbits.OERR == 1)
		{
			U1STAbits.OERR = 0;
			rxb.overrun = 1;
		}

		if(U1STAbits.FERR || U1STAbits.PERR)
			clear = U1RXREG;

		IFS0bits.U1EIF = 0;
	}		
}
```