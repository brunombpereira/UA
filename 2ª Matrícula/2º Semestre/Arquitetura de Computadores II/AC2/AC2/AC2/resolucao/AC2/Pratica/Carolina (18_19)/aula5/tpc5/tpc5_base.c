#include <detpic32.h>
#include "escape_seq.h"

#define true 1
#define false 0

int draw(int xi, int yi, int xf)
{
   int color[]={CYAN, RED, GREEN, BLUE};
   static int first = true;
   static int state = 0;
   static int xref, yref;
   static int xwidth, ywidth;
   static int x, y;

   if(first)
   {
      first = false;
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
   }
   textcolor(color[x & 0x0003]);
   gotoxy(x, y);
   putChar('+');
   switch(state)
   {
      case 0:
         if(++x >= xref + xwidth)
         {
            x = xref + xwidth - 1;
            y = yref + 1;
            state = 1;
         }
         break;
      case 1:
         if(++y >= yref + ywidth)
         {
            x = xref + xwidth - 2;
            y = yref + ywidth - 1;
            state = 2;
         }
         break;
      case 2:
         if(--x < xref)
         {
            x = xref;
            y = yref + ywidth - 2; 
            state = 3;
         }
         break;
      case 3:
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
   }
   return xref <= xf ? false : true;
}

void delay(int ms)
{
   for(; ms > 0; ms--)
   {
      resetCoreTimer();
      while(readCoreTimer() < 20000);
   }
}

int main(void)
{
   clrscr();
   do
   {
      delay(20);
   } while(draw(70, 20, 40));
   return 0;
}

