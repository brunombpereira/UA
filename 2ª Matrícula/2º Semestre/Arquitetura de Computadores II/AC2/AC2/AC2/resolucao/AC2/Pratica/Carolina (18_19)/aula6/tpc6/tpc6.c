#include <detpic32.h>
#include "escape_seq.h"

#define true 1
#define false 0

void send2displays(unsigned char value) {
   static const char display7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D,  0x07, 0x7F, 0x67, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
   static char displayFlag = 0;  
   int dh = value >> 4;
   int dl = value & 0x0F;


   if (displayFlag == 0)
   {
      LATDbits.LATD6 = 0;
      LATDbits.LATD5 = 1;
      LATB = (LATB & 0x00FF) | display7Scodes[dl] << 8;
   }else
   {
      LATDbits.LATD6 = 1;
      LATDbits.LATD5 = 0;
      LATB = (LATB & 0x00FF) | display7Scodes[dh] << 8;
      
   }
   displayFlag = !displayFlag;
}
         // função para converter para BCD //
unsigned char bintoBCD(unsigned char value){
   return ((value/10) << 4) + (value % 10); 

}

int draw(int xi, int yi, int xf)
{
   static int color[]={CYAN, RED, GREEN, BLUE};
   static int state = 4;
   static int xref, yref;
   static int xwidth, ywidth;
   static int x, y;

   textcolor(color[x & 0x0003]);
   gotoxy(x, y);
   switch(state)
   {
      case 0:
         putChar('+');
         if(++x >= xref + xwidth)
         {
            x = xref + xwidth - 1;
            y = yref + 1;
            state = 1;
         }
         break;
      case 1:
         putChar('+');
         if(++y >= yref + ywidth)
         {
            x = xref + xwidth - 2;
            y = yref + ywidth - 1;
            state = 2;
         }
         break;
      case 2:
         putChar('+');
         if(--x < xref)
         {
            x = xref;
            y = yref + ywidth - 2; 
            state = 3;
         }
         break;
      case 3:
         putChar('+');
         if(--y <= yref)
         {
            xref -= 2;
            yref -= 1;
            xwidth += 4;
            ywidth += 2;
            x = xref;
            y = yref;
            state = 0;
         }
         break;
      case 4:
         xwidth = 5;
         ywidth = 3;
         xref = x = xi - 2;
         yref = y = yi - 1;
         gotoxy(xi, yi);
         textattr(BLINK);
         textcolor(WHITE);
         putChar('*');
         textattr(RESETATTR);
         state = 0;
         break;
   }
   return xref <= xf ? true : false;
}

void delay(int ms)
{
   for(; ms > 0; ms--)
   {
      resetCoreTimer();
      while(readCoreTimer() < 20000);
   }
}

volatile int level;  // Global variable

int main(void)
{
   int delayValue;
   int done;
   unsigned int counter;
	TRISE = TRISE & 0xFFF0;	//LEDs

	TRISD= TRISD & 0xFF9F;	//disp
	TRISB = TRISB & 0x00FF;	// RB dos disp
   clrscr();
			TRISBbits.TRISB4 = 1;	  // RB4 configured as input
			AD1PCFGbits.PCFG4 = 0;    // RB4 configured as analog 
			AD1CON1bits.SSRC = 7;     //modo "auto convert"
			AD1CON1bits.CLRASAM = 1;  //so há conversão quando se dá ordem 
					          //  interrupt is generated. At the same time, 
		                                  //  hardware clears the ASAM bit 
			AD1CON3bits.SAMC = 16;    // Sample time is 16 TAD (TAD = 100 ns) 
			AD1CON2bits.SMPI = 3;     // Interrupt is generated after XX samples (XX-1)
		                                  //  (replace XX by the desired number of 
		                                  //  consecutive samples)  
					          // informação disponível no registo(ADC1BUFXX-1)
			AD1CHSbits.CH0SA = 4;     // replace x by the desiredinput  
		                                  //  analog channel (0 to 15) 
			AD1CON1bits.ON = 1;       // Enable A/D converter 
	                                  //  This must the last command of the A/D
	                                  //  configuration sequence input (AN4) 
			IPC6bits.AD1IP = 2; // configure priority of A/D interrupts
			IFS1bits.AD1IF = 0; // clear A/D interrupt flag
			IEC1bits.AD1IE = 1; // enable A/D interrupts
			EnableInterrupts();	
  
   // Config I/O
   // Config Interrupts

   AD1CON1bits.ASAM = 1;
   level = 100;
   while(level == 100);
   
   delayValue = 0;
   counter = 0;
   done = 0;
	int array[] = {2, 4, 8, 16, 32};
	int freq=0;
   while(!done)
   {
      // Start ADC @ 5Hz
      if(counter % 200 == 0 ){
       AD1CON1bits.ASAM = 1;
      }
      
      if(delayValue-- == 0)
      {
         done = draw(69, 20, 40) ;
         // Compute new value for "delayValue" (as a function of "level")
        freq= array[level];
	delayValue = 1000/freq;
         // Update LEDS
	 LATE=  (LATE & 0xFFF1) |(level+1)<<1;
	 LATEbits.LATE0 =! LATEbits.LATE0;
      }
      // Refresh displays @ 100 Hz
	if(counter % 10 ==0){
		if(PORTBbits.RB0==0){
		send2displays(bintoBCD(level+1));
		}
		else
		send2displays(bintoBCD(freq));

	}	
           counter++;
      delay(1);
   }
   return 0;
}

// ADC Interrupt Service Routine:
//   Read ADC value
//   Compute level and assign it to global variable "level"
void _int_(27) isr_adc(void){
	int *p= (int *)(&ADC1BUF0);
	int soma=0;
	int i;
	for(i=0; i< 4; i++)
	{	
		soma = soma+ p[i*4];
	}
	int media = soma/4;
      	level= (media*5) /1024;
	IFS1bits.AD1IF= 0 ;
}
