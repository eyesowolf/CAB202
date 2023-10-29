#include <avr/io.h>
#include <avr/interrupt.h>

#include "timer.h"

/** EX: 7.6

The stopwatch will be controlled by pushbuttons S1, S2, and S4.

TASK: Write an interrupt service routine for PORTA, that will be called
whenever a pushbutton is pressed.

This ISR should check which pin generated the interrupt, and perform
one of the following actions:

- If S1 is pressed, start the stopwatch.
- If S2 is pressed, stop the stopwatch.
- If S4 is pressed, reset the stopwatch to 0.

HINT: Refer to datasheet Section 8.2 Interrupt Vector Mapping on p. 63
to find the required interrupt vector name.

NOTE: Each pin has its own interrupt flag, and you must only clear the
interrupt flag for the pin that generated the interrupt.

Refer to datasheet Section 17.5.10 Interrupt Flags on p. 163 for
information on how to clear these interrupt flags.
*/

ISR(PORTA_PORT_vect){
    if (PORTA.INTFLAGS & PIN4_bm) {
        is_counting = 1;
        
        PORTA.INTFLAGS = PIN4_bm;
    }
    if (PORTA.INTFLAGS & PIN5_bm) {
        is_counting = 0;

        PORTA.INTFLAGS = PIN5_bm;
    }
    if (PORTA.INTFLAGS & PIN7_bm) {
        elapsed_time = 0;

        PORTA.INTFLAGS = PIN7_bm;
    }
}   


/** CODE: Write your code for Ex 7.6 above this line. */
