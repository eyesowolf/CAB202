#include "buttons.h"

/** Tutorial 10

INTRODUCTION:

In this week's tutorial you will be implementing pushbutton handling,
including debouncing, and implementing a state machine using enum
and switch-case statements.

The Tutorial 10 exercises, once completed, should implement the
state machine as documented in state_machine_tut10.png, and all
pushbuttons should be debounced.

Pushbutton handling on the QUTy is a core requirement for Assessment 2,
and use of a state machine is the preferred way to get the required
behavior for the different modes that must be implemented (as well as
for serial protocol handling which will be discussed in Week 11).
*/

/** EX: 10.0

TASK: Declare an enumerated type (enum) that can hold the values of each state
required to implement the state machine in "state_machine_tut10.png".

Use meaningful names for each enum value.

TIP: Use the "typedef" keyword to create a type alias for your enum.
*/

typedef enum{
    OFF,
    CONFIRM_ON,
    ON,
    CONFIRM_OFF
} led_state;

/** CODE: Write your code for Ex 10.0 above this line. */

int main(void)
{
    buttons_init();

    /** EX: 10.1

    TASK: Declare a variable of the enumerated type you declared above.

    Initialise this variable with the initial state of the state machine.
    */

   led_state state = OFF;

    /** CODE: Write your code for Ex 10.1 above this line. */

    uint8_t pb_state;
    uint8_t pb_state_r;
    uint16_t pb_falling_edge;

    while (1)
    {
        /** EX: 10.2

        We have already written some code in "buttons.c" which uses periodic
        interrupts to sample the state of the pushbuttons for you; the state
        of the pushbuttons will be available in variable "pb_debounced_state".

        This variable does not yet contain the debounced state of the
        pushbuttons, we will do that in Ex 10.4.

        TASK: Write code to detect pushbutton press events for S1-S4
        (i.e., detect the falling edge of the bits in "pb_debounced_state").

        Store the output of this detection in the variable "pb_falling_edge".

        HINT: To detect an edge, you will need to keep track of the previous and
        current state of the pushbuttons.

        This will require you to declare a variable whose value will be
        preserved between iterations of this while loop.
        */

        pb_state_r = pb_state;
        pb_state = pb_debounced_state;

        pb_falling_edge = (pb_state ^ pb_state_r) & ~pb_state;


        /** CODE: Write your code for Ex 10.2 above this line. */

        /** EX: 10.3

        TASK: Write a switch-case statement below that implements the state machine
        documented in "state_machine_tut10.png".

        Your switch statement should test the value of the variable declared
        in Ex 10.1. A case should be defined for every state in the state machine.

        Use the "pb_falling_edge" variable from Ex 10.2 to trigger the
        appropriate transitions between states.

        LED DP should be controlled based on the current state of your state machine.
        */

       PORTB.DIRSET = PIN5_bm;

        switch (state){
            case OFF:
                PORTB.OUTSET = PIN5_bm;
                if (pb_falling_edge & PIN4_bm){
                    state = CONFIRM_ON;
                }
                break;
            case CONFIRM_ON:
                if (pb_falling_edge & PIN5_bm){
                    state = ON;
                } else if (pb_falling_edge & (PIN4_bm | PIN6_bm | PIN7_bm))
                {
                    state = OFF;
                }
                break;
            case ON:
                PORTB.OUTCLR = PIN5_bm;
                if (pb_falling_edge & PIN6_bm){
                    state = CONFIRM_OFF;
                }
                break;
            case CONFIRM_OFF:
                if (pb_falling_edge & PIN7_bm){
                    state = OFF;
                } else if (pb_falling_edge & (PIN4_bm | PIN5_bm | PIN6_bm))
                {
                    state = ON;
                }
                break;
            default:
                break;
        }


        /** CODE: Write your code for Ex 10.3 above this line. */
    }

    /** EX: 10.4

    TASK: Modify the code in "buttons.c" such that the variable "pb_debounced_state"
    holds a debounced version of the pushbutton state, rather than just a raw sample
    of PORTA.IN.
    */

    /** CODE: Write your code for Ex 10.4 in buttons.c. */
}
