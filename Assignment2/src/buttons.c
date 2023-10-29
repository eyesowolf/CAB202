#include <avr/io.h>
#include <avr/interrupt.h>

void button_init(void)
{
    PORTA.PIN4CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN5CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN6CTRL = PORT_PULLUPEN_bm;
    PORTA.PIN7CTRL = PORT_PULLUPEN_bm;
}

volatile uint8_t pb_debounced_state = 0xFF;

void debounce_buttons(void){
    static uint8_t count0 = 0;
    static uint8_t count1 = 0;
    uint8_t pb_sample = PORTA.IN;
    uint8_t pb_changed = pb_debounced_state ^ pb_sample;
    count1 = (count1 ^ count0) & pb_changed;
    count0 = ~count0 & pb_changed;
    pb_debounced_state ^= (count1 & count0);
}