#ifdef __XC32
#include <xc.h>          /* Defines special function registers, CP0 regs  */
#endif

#include <stdint.h>         /* For uint32_t definition                        */
#include <stdbool.h>        /* For true/false definition                      */

#include "user.h"           /* User funct/params, such as InitApp             */
#include "UART.h"
#include "game.h"

int32_t main(void)      
{
    InitApp();              //Initialize I/O and Peripherals for application
    Bets();                 //The game function
}
