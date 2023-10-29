#include <avr/io.h>
#include <stdint.h>

char uart_print_buf[8];

void uart_init(void)
{
    PORTB.DIRSET = PIN2_bm;
    USART0.BAUD = 1389;
    USART0.CTRLB = USART_RXEN_bm | USART_TXEN_bm;
}

char uart_getc(void)
{
    while (!(USART0.STATUS & USART_RXCIF_bm))
        ;
    return USART0.RXDATAL;
}

void uart_putc(char c)
{
    while (!(USART0.STATUS & USART_DREIF_bm))
        ;
    USART0.TXDATAL = c;
}

void uart_puts_int(char* s){
    char *ptr = s;
    while (*ptr != '\0'){
        uart_putc(*ptr);
        ptr++;
    }
}

void uart_puts(char* s){
    uart_puts_int(s);
    uart_putc('\n');
}

void uart_puti(char* s, uint32_t i){
    uart_puts_int(s);
    for(int j = 7; j >= 0; j--){
        uart_print_buf[j] = (i & 15) + 48;
        if (uart_print_buf[j] > 57){
            uart_print_buf[j] += 7;
        }
        i >>= 4;
    }
    uart_print_buf[8] = 0;
    uart_puts_int(uart_print_buf);
    uart_putc('\n');
}