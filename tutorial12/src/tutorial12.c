#include <avr/interrupt.h>

#include "buzzer.h"
#include "display.h"
#include "display_macros.h"
#include "initialisation.h"
#include "timer.h"

/** Tutorial 12

INTRODUCTION:

In this week's tutorial, you will be implementing a music player that
is controlled via the four pushbuttons.

The music player indicates that a pushbutton has been pressed by
producing a sound on the buzzer and illuminating a pattern on the
7-segment display.

These outputs are described in the table below:

State | Buzzer frequency | 7-segment display
------|------------------|------------------
TONE1 | 486 * 2^(-5/12)  | Segments EF (LHS)
TONE2 | 486 * 2^(-8/12)  | Segments BC (LHS)
TONE3 | 486              | Segments EF (RHS)
TONE4 | 486 * 2^(-17/12) | Segments BC (RHS)

where XY are the last two digits of your student number.

Additionally, the buzzer should be silent, and the 7-segment display
should be dim, as soon as pushbuttons S1, S2, S3, and S4 are released.
*/

/** EX: 12.0

TASK: Declare an enumerated type (enum) that can hold the values of each
state required to implement the state machine in "state_machine_tut12.png".
*/

typedef enum {
    WAIT,
    TONE1,
    TONE2,
    TONE3,
    TONE4
} CURRENT_STATE;

/** CODE: Write your code for Ex 12.0 above this line. */

int main(void)
{
    cli();
    button_init();
    spi_init();
    pwm_init();
    timer_init();
    sei();

    update_display(DISP_OFF, DISP_OFF);

    /** EX: 12.1

    TASK: Declare a variable for the enumerated type declared above with
    the initial state of the state machine.
    */

    CURRENT_STATE state = WAIT;

    /** CODE: Write your code for Ex 12.1 above this line. */

    /** EX: 12.2

    See include/initialisation.h.
    */

    /** EX: 12.3

    See src/buzzer.c.
    */

    buzzer_off();

    /** EX: 12.4

    See src/timer.c.
    */

    uint8_t pb_state_r;
    uint8_t pb_state = pb_debounced_state;

    while (1)
    {
        /** EX 12.5

        TASK: Implement the state machine in "state_machine_tut12.png".

        The following variables and functions are available in this
        scope:

        - volatile uint8_t pb_debounced_state
        - buzzer_on(const uint8_t tone)
        - buzzer_off(void)
        - update_display(const uint8_t left, const uint8_t right)

        NOTE: You will need to detect both falling and rising edges from
        the pushbuttons.
        */

        pb_state_r = pb_state;
        pb_state = pb_debounced_state;

        switch(state){
            case WAIT:
                buzzer_off();
                update_display(DISP_OFF,DISP_OFF);
                if (((pb_state_r ^ pb_state) & ~pb_state) & PIN4_bm){
                    state = TONE1;
                } else if (((pb_state_r ^ pb_state) & ~pb_state) & PIN5_bm){
                    state = TONE2;
                } else if (((pb_state_r ^ pb_state) & ~pb_state) & PIN6_bm){
                    state = TONE3;
                } else if (((pb_state_r ^ pb_state) & ~pb_state) & PIN7_bm){
                    state = TONE4;
                }
                break;
            case TONE1:
                buzzer_on(0);
                update_display(62,255);
                if ((pb_state_r ^ pb_state) & pb_state){
                    state = WAIT;
                }
                break;
            case TONE2:
                buzzer_on(1);
                update_display(107,255);
                if ((pb_state_r ^ pb_state) & pb_state){
                    state = WAIT;
                }
                break;
            case TONE3:
                buzzer_on(2);
                update_display(255,62);
                if ((pb_state_r ^ pb_state) & pb_state){
                    state = WAIT;
                }
                break;
            case TONE4:
                buzzer_on(3);
                update_display(255,107);
                if ((pb_state_r ^ pb_state) & pb_state){
                    state = WAIT;
                }
                break;
            default:
                break;
        }

        /** CODE: Write your code for Ex 12.5 above this line. */
    }
}
