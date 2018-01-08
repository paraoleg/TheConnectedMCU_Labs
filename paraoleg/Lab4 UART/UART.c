#include "UART.h"

void UART4_init (void)
{
    RPF8R = 2; // PPS for U4RX from pin F2
    U4RXR = 11; // PPS for U4TX to pin F8
    
    U4STAbits.UTXEN = 1;   // enable transmit pin
    U4STAbits.URXEN = 1;   // enable receive pin
    U4BRG           = ((100 * 1000000) / (16 * 115200)) - 1;
    U4MODEbits.ON   = 1;   // enable UART
}

char UART4_getc(void) {
    while (!U4STAbits.URXDA)
        ; // wait until character received
    return U4RXREG; // read character
}

void UART4_putc (char c)
{
    while (U4STAbits.UTXBF)
        ;  // wait until transmit buffer empty
    U4TXREG = c;  // transmit character
}

void UART4_puts (char *s)
{
    while (*s != '\0')
        UART4_putc (*s++);
}


void UART4_test (void)
{
    char c;

    UART4_puts("Hello, World!\r\n");
    UART4_puts("Please press a key.\r\n");
    
    for (;;)
    {
        c = UART4_getc();
        UART4_putc('[');
        UART4_putc (c);
        UART4_puts("]\r\n"); 
    }
}
