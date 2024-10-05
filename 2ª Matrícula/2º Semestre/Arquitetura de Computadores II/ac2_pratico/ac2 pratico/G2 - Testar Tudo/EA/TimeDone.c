#include <detpic32.h>

unsigned int timeDone(int ms, unsigned char reset) 
{ 
    unsigned int curCount; 
    unsigned int retValue = 0; 
    if (reset > 0) { 
        resetCoreTimer(); 
    } 
    else { 
        curCount = readCoreTimer(); 
    if (curCount > (K * ms)) 
        retValue = curCount / K; 
    } 
    return retValue; 
} 