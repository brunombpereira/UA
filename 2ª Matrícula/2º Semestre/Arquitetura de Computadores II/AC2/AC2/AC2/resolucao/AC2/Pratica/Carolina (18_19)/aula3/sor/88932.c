#include <detpic32.h>

void delay(int);
void johnson(void);
void contador(void);

void main(void) {
	int scanner;
	do {
		printStr("\nMenu:\n 1. Contador Johnson com deslocamento a esquerda e direita\n 2. Contador crescente\n");
		scanner = readInt10();
		printStr("\n");

		if (scanner == 1) {
			johnson();
		}
		else if (scanner == 2) {
			contador();
		}
	}

	while ((scanner != 1) | (scanner != 2));
}

void delay(int ms) {
	for ( ; ms > 0; ms--) {
		resetCoreTimer();
		while (readCoreTimer() < 20000);
	}
}

void johnson(void) {
	TRISB = (TRISB | 0x0004);				// configura como entrada (poe a 1 bit 0) ????????????
	TRISE = (TRISE & 0xFFF0);				// configura como saida (poe a 0 bit 3-0)
	LATE = 0;								// saidas comecam a 0 (reset)
	int info= LATE;							// é redundante ou nao ???????;
	while(1) {
		int switch0 = PORTBbits.RB2;		// le valor do interruptor (define se descola p esquerda ou direita) ?????????????
		
		if (switch0 == 0) { 				// deslocamento a esquerda
			if (LATEbits.LATE3 == 0) {		// analisar bit mais a esquerda: se estiver a 0, coloca uns
				info = info << 1;			// desloca 1 vez a esquerda
				info = (info | 0x0001);		// poe novo bit inserido a 1
			}
			else info = info << 1;			// se estiver a 1, coloca zeros
		}
		else {								// deslocamento a direita
			if (LATEbits.LATE0 == 0) {		// ver bit mais a direta: se estiver a 0, coloca uns
				info = info >> 1;
				info = (info | 0x0008);		// coloca novo bit (o mais a esquerda) a 1
			}
			else info = info >> 1;
		}
		LATE = info;						// atualizar contador 
		delay(667); 						// frequencia a 1.5Hz, logo atraso de (1/1.5)ms		
	}
}

void contador(void) {
	// printf("entrou");
	TRISE = (TRISE & 0xFFF0);				// configura como saida (poe a 0 bit 3-0)
	int count = 0;
	while(1) {
	//while (LATE != 0x000F) {				//para contar apenas ate 16 e parar
		LATE = count;
		count++;
		delay(250);							// frequencia a 4Hz
	}
}

