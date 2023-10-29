#include <avr/io.h>

void pwm_init(void)
{
    PORTB.OUTSET = PIN0_bm;
    PORTB.DIRSET = PIN0_bm;
    TCA0.SINGLE.CTRLB=TCA_SINGLE_WGMODE_SINGLESLOPE_gc | TCA_SINGLE_CMP0EN_bm;
    TCA0.SINGLE.PER = 0;
    TCA0.SINGLE.CMP0 = 0;
    TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;
}