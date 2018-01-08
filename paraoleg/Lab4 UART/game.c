#include "game.h"
#include "UART.h"
#include <stdio.h>
#include <stdint.h>
#include <sys/attribs.h>

int Get_Guess(void) {   //read number from UART
    char c;
    int n=0, done=0;
    
    while (1) {
        c = UART4_getc();
        UART4_putc(c); // echo back character
        if ((c >= '0') && (c <= '9')) {
            n *= 10;
            n += c-'0';
        } else {
            if (c == '\r')
                return n;
            else
                return ILLEGAL_CHAR;
        }
    }
}


void Bets(void) {           //main game "Bets", 
    int points = 1500;
    
    int number, randomNumber;
    int bet = 0;
    char buffer[80];
    
    srand(rand_seed);       //generate random number
    
    while ( points > 0 ) {
        
        sprintf(buffer, "\r\n\nYou have %d guesses left.\r\n", points);
        UART4_puts(buffer);
        
        UART4_puts("\r\nChoose number: 0-9\r\n");
        number = Get_Guess();
        
                
        UART4_puts("\r\nTake a bet: 0-9\r\n");
        bet = Get_Guess();
        
        
        if (number == ILLEGAL_CHAR || bet == ILLEGAL_CHAR) {
                UART4_puts("That's not a number! You lost your bet.\r\n");
        }
        
        else {
            if ( bet < 0 ) {
                UART4_puts("Bye-bye, cheater!\r\n");
                break;
            }
        
            if ( bet > points ) { 
                bet = points;
                sprintf(buffer, "Your bet is %d\n", bet);
                UART4_puts(buffer);
            }
                
            points -= bet;
            randomNumber = rand() % 10;
            
            sprintf(buffer, "Number is: %d\r\n", randomNumber);
            UART4_puts(buffer);
                
            if ( randomNumber == number ) {
                points = points + (bet * 10);
                UART4_puts("You win!\r\n");
            } 
            else {
                UART4_puts("You lose\r\n");
            }
        }
    }
    
    UART4_puts("Game over\r\n");
        
    
}

void initTimer2AndIC3(void) {
    T2CON = 0; // clear timer settings to defaults
    T2CONbits.TCKPS = 7; // divide clock by 256 with prescaler
    TMR2 = 0;
    PR2 = 39062;
    
    IPC2bits.T2IP = 3;
    IPC2bits.T2IS = 0;
    IFS0bits.T2IF = 0;
    IEC0bits.T2IE = 1;
 
    IC3R = 4;
    // Configure IC3 control register
    IC3CONbits.C32 = 1;    // 32 bit mode
    IC3CONbits.FEDGE = 0;
    IC3CONbits.ICTMR = 0; // Select timer 2
    IC3CONbits.ICM = 3;
    IC3CONbits.ICI = 0;
    IC3CONbits.SIDL = 1;
    IC3CONbits.ON = 1;
     
    
    IPC4bits.IC3IP = 2;
    IPC4bits.IC3IS = 2;
    IFS0bits.IC3IF = 0;
    IEC0bits.IC3IE = 1;
    
}

void __ISR(_INPUT_CAPTURE_3_VECTOR,IPL2SRS) Capture3(void){ //generate random seed
    if(CNENFbits.CNIEF1){
        rand_seed = IC3BUF;
    }
    IFS3CLR = _IFS3_CNEIF_MASK;
}

