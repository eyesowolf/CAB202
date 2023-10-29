#include <avr/io.h>
#include <avr/interrupt.h>
#include "display.h"
#include "spi.h"
#include "uart.h"

volatile uint8_t left_byte = DISP_OFF;
volatile uint8_t right_byte = DISP_OFF;

void update_display(const uint8_t left, const uint8_t right)
{
    left_byte = left | DISP_LHS;
    right_byte = right;
}

ISR(SPI0_INT_vect)
{
    PORTA.OUTCLR = PIN1_bm;
    PORTA.OUTSET = PIN1_bm;
    SPI0.INTFLAGS = (SPI_IF_bm | SPI_DREIE_bm);
}
