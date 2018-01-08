#ifdef __XC32
#include <xc.h>          /* Defines special function registers, CP0 regs  */
#endif

#include <stdint.h>          /* For uint32_t definition                       */
#include <stdbool.h>         /* For true/false definition                     */
#include "user.h"            /* variables/params used by user.c               */


/* Setup analog functionality and port direction */
void InitApp(void) {
    

    // LED output
    // Disable analog mode for pins
    ANSELG &= ~((1 << 6) | (1 << 15));
    ANSELB &= ~(1 << 11);
    
    // Set direction to output for pins
    TTRISG &= ~((1 << 6) | (1 << 15));
    TRISB &= ~(1 << 11);
    
     // Disable analog mode for D4
    PORTDbits.RD4 = 0; //  For LED2 on PORTD pin 4 is no analog option so ANSELDbits.ANSD4 = 0 will not compile
        // Set direction to output for D4
    TRISD &= ~(1 << 4);
        
    // Initialize outputs for other LEDs

    // Turn on LEDs for testing

    LD4_PORT_BIT = 1; // Turm on G15
    LD3_PORT_BIT = 1; // Turm on B11
    LD2_PORT_BIT = 1; // Turm on D4
    LD1_PORT_BIT = 1; // Turm on G6
    
    // Stop program here
    // while(1); endless loop
    
    // Turn off LEDs for testing

    /*LATGbits.LATG15 = 0; // Turm off G15
    LD4_PORT_BIT = 0; // Turm off1 B11
    LD3_PORT_BIT = 0; // Turm off D4
    LD2_PORT_BIT = 0; // Turm off D4
    LD1_PORT_BIT = 0; // Turm off G6*/
    
    // BTN1 input
    // Disable analog mode
    ANSELA &= ~(1 << 5);
    // Set directions to input
    TRISA |= (1 << 5)|(1 << 4);
    
    // Test switches
    while (1) {
	    LD1_PORT_BIT = BTN1_PORT_BIT;
	    LD2_PORT_BIT = BTN2_PORT_BIT;
    };
}

void Delay(int n) {
    volatile int i;
    for (i = 0; i < n; i++) {
    }
}

void Flash_LED(void) {
    int delay_count;
    while (1) {
        if (BTN1_PORT_BIT == 1) {
            // switch is pressed
            delay_count = 1000000;
        } else {
            // switch is not pressed
            delay_count = 4000000;
        }
        PORTGbits.RG6 = 1; // Turn on LED
        Delay(delay_count);
        PORTGbits.RG6 = 0; // Turn off LED
        Delay(delay_count);
    }
}

void Scan_LEDs(void) {

	int LED_state = 1; // 1 on (initial value), 0 off
	int delay_count=1000000;

	while (1) {
		if (BTN1_PORT_BIT == 1) { //first button is pressed
			delay_count = 300000;
		} 
		else { 
			delay_count = 1000000;
		}

		if (BTN2_PORT_BIT == 1) { //second button is pressed
		LD1_PORT_BIT = 0;
		LD2_PORT_BIT = 0;
		LD3_PORT_BIT = 0;
		LD4_PORT_BIT = 0;
		} 
		else {
			LD1_PORT_BIT = LED_state;
			Delay(delay_count);
			LD2_PORT_BIT = LED_state;
			Delay(delay_count);
			LD3_PORT_BIT = LED_state;
			Delay(delay_count);
			LD4_PORT_BIT = LED_state;
			Delay(delay_count);

			// next time, set LEDs to opposite state

			LED_state = 1 - LED_state;
		}
	}
}

