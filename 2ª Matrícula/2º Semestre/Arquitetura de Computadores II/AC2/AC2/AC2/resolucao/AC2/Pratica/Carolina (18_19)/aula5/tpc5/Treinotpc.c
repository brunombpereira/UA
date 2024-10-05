#include <detpic32.h>
#include "escape_seq.h"

#define true 1
#define false 0
//funçoes
void delay(int ms);
void send2displays(unsigned char value) ;
int draw(int xi, int yi, int xf);
unsigned char BCD(unsigned char value);

int main(void)
{
  

   TRISBbits.TRISB4=1;  // RB4 digital output disconnected
   AD1PCFGbits.PCFG4=0; // configured as analog input (AN4)

   AD1CON1bits.SSRC=7;  //onversion trigger selection bits: in this
                        //mode an internal counter ends sampling and starts conversion
            
   AD1CON1bits.CLRASAM=1; // Stop conversions when the 1st A/D converter
                          //interrupt is generated. At the same time,
                          //hardware clears the ASAM bit

   AD1CON3bits.SAMC=16;    //Sample time is 16 TAD (TAD = 100 ns)
   AD1CON2bits.SMPI=0;     //Interrupt is generated after XX samples
                           //(replace XX by the desired number of
                           //consecutive samples)

   AD1CHSbits.CH0SA=4; //AN4 input A/D converter

   AD1CON1bits.ON=1; //ENABLE A/D converter

   TRISE=(TRISE & 0xFFF0); //RE0-3 outputs -
   //RD6-5 outputs
   TRISD=TRISDbits.TRISD5 =0; 
   TRISD=TRISDbits.TRISD6 =0;

   TRISB=(TRISB & 0x80FF) | 0x0001; //RB14-8 outputs RB0 input

   int conta, time, ADC;

   int f[] = {2,4,8,16,32}; //frequencias possiveis (5niveis)
   
   clrscr();

    do{
      AD1CON1bits.ASAM=1;          //Start conversion
      
      while(IFS1bits.AD1IF == 0); // wait while conversion not done (AD1IF == 0)
      //int var =ADC1BUF0;
      //printf("açaççaça %d\n", var);
      conta=(ADC1BUF0*5)/1024;     //tensao* 5 (valores de f[]) /2¹⁰
      time = 1000/f[conta ];       // FreqDeRefrescamento/f[conta] 
     
      
      int i =0;
         
         while(i<=time){            //comparaçao
            ADC=conta+1;
            
            if(PORTBbits.RB3==1)    // switch3 = 1
               send2displays(BCD(f[conta])); // passa a freq de 2 a 32 hz conforme o conta               
            else                    // switch0 = 1
               send2displays(ADC);  
               //RB0=0 mostra os niveis de 1 a 5         
        
         delay(1); // 1 ms para freq de 1000hz
           i++;         //incrementa
         }
         
      IFS1bits.AD1IF=0; // end
      
      LATE=(LATE & 0xFFF1) | ADC << 1;    //Passa para os leds 
      LATEbits.LATE0=!LATEbits.LATE0;     //faz piscar
   }while(draw(70, 20, 40));

    return 0;
}

//funçoes
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
unsigned char BCD(unsigned char value){
   return ((value/10) << 4) + (value % 10); 

}

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



