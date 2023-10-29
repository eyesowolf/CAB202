#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdio.h>

/** CODE: Write your code for Ex 7.7 below this line. */
#include "initialisation.h"
#include "timer.h"

/** CODE: Write your code for Ex 7.7 above this line. */
#include "qutyio.h"

/** Tutorial 07

INTRODUCTION:

In this week's tutorial you will be writing C code to implement
a stopwatch. This stopwatch will start counting up when S1 is
pressed and display the elapsed time in hexadecimal sixteenths
of a second, on the 7-segment display.

Once the stopwatch reaches 255, it will stop increasing.

Three pushbuttons will be used to control the stopwatch:
- Button S1 will be used to start the stopwatch
- Button S2 will be used to stop the stopwatch
- Button S4 will be used to reset the time back to 0
*/

/** EX: 7.0

See include/initialisation.h.
*/

/** EX: 7.1

See include/initialisation.h.
*/

/** EX: 7.2

See src/timer.c.
*/

/** EX: 7.3

See src/timer.c.
*/

/** EX: 7.4

See src/timer.c.
*/

/** EX: 7.5

See include/timer.h.
*/

/** EX: 7.6

See src/buttons.c.
*/

int main(void)
{
    // Configures pins PA1, PC0, and PC2, to drive the 7-segment display
    display_init();
    // Drives DISP EN net HIGH
    display_on();

    /** EX: 7.7

    TASK: Include the header file containing the initialisation
    functions you wrote in Ex 7.0, and call these functions below.

    NOTE: This header file should be included at the top of this file.
    */
   clock_init();
   buttons_init();


    /** CODE: Write your code for Ex 7.7 above this line. */

    // This program is interrupt-driven and therefore does not need any
    // additional code in main().
    while (1)
        ; // Loop indefinitely
}
