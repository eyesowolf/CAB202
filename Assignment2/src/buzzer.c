#include <avr/io.h>
#include <stdint.h>
#include "buzzer.h"

uint64_t TONE1_PER = 9146;
uint64_t TONE2_PER = 10880;
uint64_t TONE3_PER = 6852;
uint64_t TONE4_PER = 18290;

void buzzer_init(void){
    TONE1_PER = 9146;
    TONE2_PER = 10880;
    TONE3_PER = 6852;
    TONE4_PER = 18290;
}

void buzzer_on(const uint8_t tone)
{
    uint16_t periods[4] = {TONE1_PER, TONE2_PER, TONE3_PER, TONE4_PER};
    TCA0.SINGLE.PERBUF = periods[tone];
    TCA0.SINGLE.CMP0BUF = periods[tone] >> 1;
}

void buzzer_off(void)
{
    TCA0.SINGLE.PERBUF = 0;
    TCA0.SINGLE.CMP0BUF = 0;
}

void increase_freq(void){
    TONE1_PER = TONE1_PER*2;
    TONE2_PER = TONE2_PER*2;
    TONE3_PER = TONE3_PER*2;
    TONE4_PER = TONE4_PER*2;
}

void decrease_freq(void){
    TONE1_PER = TONE1_PER/2;
    TONE2_PER = TONE2_PER/2;
    TONE3_PER = TONE3_PER/2;
    TONE4_PER = TONE4_PER/2;
}