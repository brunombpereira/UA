#include <detpic32.h>
volatile int counter = 0;
  int main(void)    {      
   // Configure Timer T3 (2 Hz with interrupts disabled) 
   T1CONbits.TCKPS = 3; // 1:32 prescaler (i.e. fout_presc = 625 KHz)    
   PR1 = 39062;         // Fout = (78125/2)-1   
   TMR1 = 0;            // Reset timer T3 count register    
   T1CONbits.TON = 1;   // Enable timer T3 (must be the last command of the 
                        //  timer configuration sequence)
   IPC1bits.T1IP = 2;   // Interrupt priority (must be in range [1..6])    
   IEC0bits.T1IE = 1;   // Enable timer T3 interrupts    
   IFS0bits.T1IF = 0;   // Reset timer T3 interrupt flag 

 T3CONbits.TCKPS = 5; // 1:32 prescaler (i.e. fout_presc = 625 KHz)    
   PR3 = 62499;         // pr3 = 625000/10 
   TMR3 = 0;            // Reset timer T3 count register    
   T3CONbits.TON = 1;   // Enable timer T3 (must be the last command of the 
                        //  timer configuration sequence)
   IPC3bits.T3IP = 2;   // Interrupt priority (must be in range [1..6])    
   IEC0bits.T3IE = 1;   // Enable timer T3 interrupts    
   IFS0bits.T3IF = 0;   // Reset timer T3 interrupt flag 


     EnableInterrupts();
     while(1);             
     return 0;
  }
  
  void _int_(4) isr_T1(void)       {         
   printStr("1");// print character '1'          
   IFS0bits.T1IF = 0;// Reset T1IF flag       
   }       
  void _int_(12) isr_T3(void)       {          
  printStr("3");// print character '3'               
  IFS0bits.T3IF = 0; // Reset T3 interrupt flag    
  }
