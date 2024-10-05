#include <detpic32.h>
#include "escape_seq.h"

#define true 1
#define false 0

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

   clrscr();

   // Config ADC
   // Config I/O
   // Config Interrupts

   AD1CON1bits.ASAM = 1;
   level = 100;
   while(level == 100);
   
   delayValue = 0;
   counter = 0;
   done = 0;

   while(!done)
   {
      // Start ADC @ 5Hz
      
      if(delayValue-- == 0)
      {
         done = draw(70, 20, 40) ;
         // Compute new value for "delayValue" (as a function of "level")
         // Update LEDS
      }
      // Refresh displays @ 100 Hz

      counter++;
      delay(1);
   }
   return 0;
}

// ADC Interrupt Service Routine:
//   Read ADC value
//   Compute level and assign it to global variable "level"

