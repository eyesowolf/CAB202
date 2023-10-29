#ifndef BUZZER_H
#define BUZZER_H 1

#include <avr/io.h>
#include <avr/interrupt.h>

void buzzer_on(const uint8_t tone);
void buzzer_off(void);
void increase_freq(void);
void decrease_freq(void);
void buzzer_init(void);

#endif
