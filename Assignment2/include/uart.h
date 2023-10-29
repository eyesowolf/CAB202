#include <stdint.h>

void uart_init(void);
char uart_getc(void);
void uart_putc(char c);
void uart_puts(char* s);
void uart_puti(char *s, uint32_t i);
