 #include <detpic32.h>
 void delay(int);
 void main(void)   
  {  
    LATE= LATE & 0xFFF0;   
    int pattern[]={0x00, 0x01,0x03,0x07,0x0F,0x0E, 0x0C, 0x8}                             
    TRISE = (TRISE & 0xFFF0);  // RE[3..0] configured as output  (READ MODIFY)
   int conter=0;
       
     while(1)     
      {    
      	int v = PORTBbits.RB2 ;	// ler o switch RB2
      		if(v==1)		//se RB2=0 desloc a esquerda
      			conter= (conter+1)& 0x0007;
          
      		else //desloc a direita
      			conter=(conter-1)& 0x0007;
        delay(666);         //  1.5hz  
           LATE=(LATE & 0xFFF0)|pattern[conter] ;   
       }  

   }
  
   void delay(int ms) 
{ 
  for(; ms > 0; ms--) 
  { 
    resetCoreTimer(); 
  while(readCoreTimer() < 20000); 
    } 
} 