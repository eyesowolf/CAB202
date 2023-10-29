#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "adc.h"
#include "spi.h"
#include "display.h"
#include "buttons.h"
#include "buzzer.h"
#include "uart.h"

volatile uint16_t timer;
uint64_t next_seed;

void timer_init(void)
{
    cli();
    TCB0.CTRLB = TCB_CNTMODE_INT_gc;
    TCB0.CCMP = 3333;
    TCB0.INTCTRL = TCB_CAPT_bm;
    TCB0.CTRLA = TCB_ENABLE_bm;
    sei();
}

ISR(TCB0_INT_vect)
{
    timer += 1;
    static int digit = 0;
    if (digit) {
        spi_write(left_byte);
    } else {
        spi_write(right_byte);
    }
    digit = !digit;
    debounce_buttons();
    TCB0.INTFLAGS = TCB_CAPT_bm;
}

