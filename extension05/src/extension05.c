/** EX: E5.0

TASK:

Your task is to write code to implement a two-tone siren
using the QUTy. You must use one of the Waveform Outputs
of TCA0 to drive the buzzer. The buzzer should always
be driven with a 50% duty cycle signal.

Your siren must alternate between the following frequencies:

    f1 = 2110 Hz with f1 active for t1 = 330 ms
    f2 = 4500 Hz with f2 active for t2 = 680 ms

where A-F are the 2nd through 7th digits of your student
number:

    nXABCDEFX
    nX115038X

EXAMPLE: If your student number was n12345678, then

A = 2, B = 3, C = 4, D = 5, E = 6, F = 7

f1 = 2230 Hz
f2 = 4450 Hz
t1 = 360 ms
t2 = 670 ms

NOTE: Your programme must be interrupt driven.

main() will call the init() function you write below
and then drop into an infinite loop. The init() function
you write MUST return to demonstrate your code is
interrupt driven.

In addition to init(), you may write any code you wish
in this file, including ISRs.
*/

#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>


void buzzer_on(const uint8_t tone)
{
    static const uint16_t periods[2] = {1579, 740};
    TCA0.SINGLE.PERBUF = periods[tone];
    TCA0.SINGLE.CMP0BUF = periods[tone] >> 1;
}

void buzzer_off(void)
{
    TCA0.SINGLE.PERBUF = 0;
    TCA0.SINGLE.CMP0BUF = 0;
}

void timer_init(void)
{
    // Interrupt every 5ms
    TCB1.CCMP = 16667;
    TCB1.INTCTRL = TCB_CAPT_bm;
    TCB1.CTRLA = TCB_ENABLE_bm;
}

void buzzer_init(void){
    PORTB.OUTSET = PIN0_bm;
    PORTB.DIRSET = PIN0_bm;
    TCA0.SINGLE.CTRLB=TCA_SINGLE_WGMODE_SINGLESLOPE_gc | TCA_SINGLE_CMP0EN_bm;
    TCA0.SINGLE.PER = 0;
    TCA0.SINGLE.CMP0 = 0;
    TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;

}

void init(void)
{
    timer_init();
    buzzer_init();
}

uint8_t counter = 0;

ISR(TCB1_INT_vect)
{
    if (counter < 66) {
        buzzer_on(0);
        counter++;
    } else if (counter < 201) {
        buzzer_on(1);
        counter++;
    } else{
        counter = 0;
    }

    TCB1.INTFLAGS = TCB_CAPT_bm;
}

/** CODE: Write your code for Ex E5.0 above this line. */
