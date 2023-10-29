/** EX: E6.0

TASK:

Your task is to write code which handles a sequence of input characters
from the UART interface, and respond with the output specified below.

On receipt of the character sequence:

- "foo" your programme should print '0' to the UART interface.
- "bar" your programme should print '1' to the UART interface.
- "foobar" your program should not print either '0' nor '1' as
  specified above, but should instead print a linefeed ('\n')
  character.

NOTE:

It is strongly recommended that you design a state machine to complete
this task, and practice drawing a state machine diagram before you
begin coding.

Your solution should use a baud rate of 9600, and 8N1 frame format.
Your solution MUST NOT use qutyio.o or qutyserial.o.

EXAMPLES:

INPUT: ...foo.bar.foo.barfoobarfood
OUTPUT: 0101\n0

0101
0(END)

INPUT: barsfoosbarforbarfoobarrforfoobarfoobarfood
OUTPUT: 1011\n\n\n0

1011


0(END)

*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

void uart_init(void)
{
    // Output enable USART0 TXD (PB2)
    PORTB.DIRSET = PIN2_bm;
    USART0.BAUD = 1389;                           // 9600 baud @ 3.3 MHz
    USART0.CTRLB = USART_RXEN_bm | USART_TXEN_bm; // Enable Tx/Rx
}

char uart_getc(void)
{
    while (!(USART0.STATUS & USART_RXCIF_bm))
        ; // Wait for data
    return USART0.RXDATAL;
}

void uart_putc(char c)
{
    while (!(USART0.STATUS & USART_DREIF_bm))
        ; // Wait for TXDATA empty
    USART0.TXDATAL = c;
}


typedef enum {
  START,
  GOT_F,
  GOT_FO,
  GOT_FOO,
  GOT_B,
  GOT_BA,
  GOT_BAR,
  GOT_FOOB,
  GOT_FOOBA,
  GOT_FOOBAR,
  WRITE_0,
  WRITE_1,
  WRITE_CR
} STATE_MACHINE;

int main(void)
{
  uart_init();

  STATE_MACHINE state = START;
  char one;
  // infinite loop for state machine:
  while (1){
    switch(state){
      case START:
        one = uart_getc();
        if (one == 'f'){
          state = GOT_F;
        } else if (one == 'b'){
          state = GOT_B;
        }
        break;
      case GOT_F:
        one = uart_getc();
        if (one == 'o'){
          state = GOT_FO;
        } else if (one == 'f') {
          state = GOT_F;
        } else if (one == 'b') {
          state = GOT_B;
        } else {
          state = START;
        }
        break;
      case GOT_FO:
        one = uart_getc();
        if (one == 'o'){
          state = GOT_FOO;
        } else if (one == 'f') {
          state = GOT_F;
        } else if (one == 'b') {
          state = GOT_B;
        } else {
          state = START;
        }
        break;
      case GOT_FOO:
        one = uart_getc();
        if (one == 'b'){
          state = GOT_FOOB;
        } else if (one == 'f') {
          uart_putc(*"0");
          state = GOT_F;
        } else {
          state = WRITE_0;
        }
        break;
      case GOT_B:
        one = uart_getc();
        if (one == 'a'){
          state = GOT_BA;
        } else if (one == 'f') {
          state = GOT_F;
        } else if (one == 'b') {
          state = GOT_B;
        } else {
          state = START;
        }
        break;
      case GOT_BA:
        one = uart_getc();
        if (one == 'r'){
          state = GOT_BAR;
        } else if (one == 'f') {
          state = GOT_F;
        } else if (one == 'b') {
          state = GOT_B;
        } else {
          state = START;
        }
        break;
      case GOT_BAR:
        state = WRITE_1;
        break;
      case GOT_FOOB:
        one = uart_getc();
        if (one == 'a'){
          state = GOT_FOOBA;
        } else if (one == 'f') {
          uart_putc(*"0");
          state = GOT_F;
        } else if (one == 'b') {
          uart_putc(*"0");
          state = GOT_B;
        } else {
          state = WRITE_0;
        }
        break;
      case GOT_FOOBA:
        one = uart_getc();
        if (one == 'r'){
          state = GOT_FOOBAR;
        } else if (one == 'f') {
          uart_putc(*"0");
          state = GOT_F;
        } else if (one == 'b') {
          uart_putc(*"0");
          state = GOT_B;
        } else {
          state = WRITE_0;
        }
        break;
      case GOT_FOOBAR:
        state = WRITE_CR;
        break;
      case WRITE_0:
        uart_putc(*"0");
        state = START;
        break;
      case WRITE_1:
        uart_putc(*"1");
        state = START;
        break;
      case WRITE_CR:
        uart_putc(*"\n");
        state = START;
        break;
      default:
        state = START;
        break;
    }
  }

}

/** CODE: Write your code for Ex E6.0 above this line. */
