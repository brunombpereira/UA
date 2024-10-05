#include <detpic32.h>


int mais(void) {
    // Configuration of digital I/O:

    // --------

    // Configuration of analog input & A/D module:

    TRISBbits.TRISBx = 1;                   // RBx digital output disconnected
    AD1PCFGbits.PCFGx = 0;                  // RBx configured as analog input
    AD1CON1bits.SSRC = 7;                   // Conversion trigger selection bits: in this mode an internal counter ends sampling and starts conversion
    AD1CON1bits.CLRASAM = 1;                // Stop conversions when the first A/D converter interrupt is generated. At the same time, hardware clears the ASAM bit
    AD1CON3bits.SAMC = 16;                  // Sample time is 16 TAD (TAD = 100ns)
    AD1CON2bits.SMPI = 0;                   // Interrupt is generated after N samples (replace N by the desired number of consecutive samples) (N - 1)
    AD1CHSbits.CH0SA = x;                   // Replace x by the desired input analog channel (0 to 15)
    AD1CON1bits.ON = 1;                     // Enable A/D converter

    // Configure interrupt system:

    IPC6bits.AD1IP = 2;                     // Configure priority of A/D interrupts
    IFS1bits.AD1IF = 0;                     // Clear A/D interrupt flag
    IEC1bits.AD1IE = 1;                     // Enable A/D interrupts
    EnableInterrupts();                     // Global interrupt enable

    AD1CON1bits.ASAM = 1;                   // Start A/D conversion

    while (1);
    return 0;                               // All activity is done by the ISR
}


// Interrupt Handler

void _int_(VECTOR) isr_adc(void) {          // Replace VECTOR by the A/D vector number - see "PIC32 family data sheet" (pages 74-76)
    printInt(ADC1BUF0, 16 | 3 << 16);       // Read conversion result (ADC1BUF0) and print it
    AD1CON1bits.ASAM = 1;                   // Start A/D conversion
    IFS1bits.AD1IF = 0;                     // Reset AD1IF flag
}