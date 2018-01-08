#ifdef __XC32
#include <xc.h>          /* Defines special function registers, CP0 regs  */
#endif

#include <stdint.h>          /* For uint32_t definition                       */
#include <stdbool.h>         /* For true/false definition                     */
#include "user.h"            /* variables/params used by user.c               */
#include <sys/attribs.h>

void DelayMs(int t) {
    volatile long int count = t * 33356;

    while (count--)
        ;
}

void InitGPIO(void) {
    /* Setup functionality and port direction */
    // LED output
    // Disable analog mode
    ANSELG &= ~((1 << 6) | (1 << 15));
    ANSELB &= ~(1 << 11);
    // Set direction to output 
    TRISG &= ~((1 << 6) | (1 << 15));
    TRISB &= ~(1 << 11);
    TRISD &= ~(1 << 4);

    // Turn off LEDs for initialization
    LD1_PORT_BIT = 0;
    LD2_PORT_BIT = 0;
    LD3_PORT_BIT = 0;
    LD4_PORT_BIT = 0;

    // Button inputs
    // Disable analog mode
    ANSELA &= ~(1 << 5);
    // Set directions to input
    TRISA |= (1 << 5)|(1 << 4)|(1 << 14);
    
    // Slide switch inputs
    // Disable Analog 
    ANSELC &= ~(1 << 1);
    ANSELE &= ~((1 << 8) | (1 << 9));
    
    
    TRISE |= (1 << 8)|(1 << 9)
    TRISC |= (1 << 1)
            
}

void InitBIOS(void) {
    /* Setup functionality and port direction */
    // LED outputs
    // Disable analog mode
    // Set directions to output
    TRISE = 0;

    // Test LEDs
    LATE = 0xff;

    // Turn off LEDs for initialization
    LATE = 0;

    // Button inputs
    // Disable Analog 
    ANSELGbits.ANSG7 = 0;
    // Set directions to input
    TRISGbits.TRISG7 = 1;
    TRISDbits.TRISD5 = 1;
    TRISFbits.TRISF1 = 1;
    TRISAbits.TRISA2 = 1;

    // ADC input for pot
    TRISBbits.TRISB5 = 1;

    // Slide switch inputs
    // Disable Analog 
    ANSELEbits.ANSE8 = 0;
    ANSELEbits.ANSE9 = 0;
    ANSELCbits.ANSC1 = 0;

    // Set directions to input
    TRISEbits.TRISE8 = 1;
    TRISEbits.TRISE9 = 1;
    TRISAbits.TRISA14 = 1;
    TRISCbits.TRISC1 = 1;

}

void InitTimer2(void) {
    T2CON = 0; // clear timer settings to defaults
    T2CONbits.TCKPS = 1; // prescale 100 MHz clock by factor of 2
    TMR2 = 0; // clear timer
    T2CONbits.ON = 1; // Start Timer 2
    // No interrupts needed.
}

void InitApp(void) {
    // Initialize peripherals
    InitGPIO();
    InitBIOS();
    InitTimer2();
    OledInit();

    // Set PREFEN mode
    // 0: Disable, 1: CPU instructions, 2. CPU instrs + data, 3. Any address
    PRECONbits.PREFEN = 3; 
    // Set PFMWS for wait states
    PRECONbits.PFMWS = 2;

    // Set up Shadow Register Sets
    PRISS = 0x76543210; /* assign shadow set #7-#1 to priority level #7-#1 ISRs */

    // Set Interrupt Controller for multi-vector mode
    INTCONSET = _INTCON_MVEC_MASK;

    // Globally enable interrupts
    __builtin_enable_interrupts();
    // Enable peripherals which can generate an interrupt
}

