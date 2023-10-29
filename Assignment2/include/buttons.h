#include <avr/io.h>
#include <avr/interrupt.h>

extern volatile uint8_t pb_debounced_state;

void button_init(void);
void debounce_buttons(void);
