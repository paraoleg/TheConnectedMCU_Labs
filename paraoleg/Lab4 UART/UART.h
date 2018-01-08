#ifndef UART_H
#define	UART_H

#include <xc.h> // include processor files - each processor file is guarded.  

void UART4_init(void);
char UART4_getc(void);
void UART4_putc (char c);
void UART4_puts (char *s);
void UART4_test (void);


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

    // TODO If C++ is being used, regular C code needs function names to have C 
    // linkage so the functions can be used by the c code. 

#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* UART_H */

