#include <detpic32.h>   

 void delay(int);
 void ex1(void) ;
 void ex2(void);

void main(void){
    int ler;


    printf("Escolha uma opção\n");
    printf("1-Exercicio1 Contador de Johnson\n");
    printf("2-Exercicio2 Contador crescente\n");

    ler=readInt10();


    if(ler==1){
      ex1();
    }
    else if(ler==2){
      ex2();
    }
    else{
      printf("Escolha invalida. Adeus!");
    }


}
 void ex1(void)   
  {  
    LATE= LATE & 0xFFF0;   // The initial value should be set 
                                //  before configuring the port as output   
    TRISE = (TRISE & 0xFFF0);  // RE[3..0] configured as output  (READ MODIFY)
    TRISB = (TRISB & 0xFFFF); // RB[3..0] configured as intput  
       
     while(1)     
      {    
      	int v = PORTBbits.RB2 ;	// ler o switch RB2

      	int led=LATE;
      	//printf("%d\n", led);
      		if(v==0)		//se RB2=0 desloc a direita
      		{

      			
      			if(LATEbits.LATE0==1)
      			{
      				//printf("ola\n");
      				led=led>>1;
      			}
      			else {
      			led=led>>1;
      			led = led| 0x0008;
      			}	// shift e acrescenta  um 0

      		}
      		else { //desloc a esquerda
      			if(LATEbits.LATE3==0)
      			{
      				//printf("adeus\n");
      				led=led<<1;
      				led = led |0x0001;

      			}
      			else led=led<<1;	// shift e acrescenta  um 0

      		}
        delay(666);         //  1.5hz  
           LATE=led ;   
       }  

   }

   
void ex2(void)
{
  TRISE = (TRISE & 0xFFF0); // RD0 configured as output
  int v=0;
  
  while(1)
  {
    LATE=v;

    delay(250); //4hz
    v++;
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