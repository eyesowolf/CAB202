#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

#include "qutyio.h"

/** EX: 7.2

To display the elapsed time on the 7-segment display, we need to count
the number of times the TCB1 CAPT interrupt is invoked.

TASK: Declare a global variable called "elapsed_time" that will be used
to store the number of 1/64th seconds that have elapsed.

Ensure this variable is sufficiently large to store 256 sixteenths of a
second.

The stopwatch should initially display 0x00.
*/

uint16_t elapsed_time = 0;

/** CODE: Write your code for Ex 7.2 above this line. */

/** EX: 7.3

To allow pushbuttons S1 and S2 to control when the stopwatch is
counting, we need to keep track of the current state of the stopwatch.

TASK: Declare a global variable called "is_counting" that keeps track
of the stopwatch's state.

The stopwatch should initially be stopped.
*/

uint8_t is_counting = 0;

/** CODE: Write your code for Ex 7.3 above this line. */

/** EX: 7.4

TASK: Declare an interrupt service routine (ISR) for the TCB1 peripheral
that was configured in Ex 7.0.

1. Find the vector number and name that correspond to the TCB1 CAPT
   interrupt.
   Refer to datasheet Section 8.2 Interrupt Vector Mapping on p. 63.
2. Find the corresponding vector definition in "iotn1626.h". This will
   look like *_vect and should correspond to the vector number
   identified in step 1.
3. Declare an ISR using the ISR(<vector>) macro, where <vector> is the
   vector definition identified in step 2.
4. If the stopwatch is currently counting, increment the "elapsed_time"
   variable by 1. Ensure that this variable does not exceed the number
   which represents 16 seconds (i.e., 256 * 1/16 seconds).
5. Update the 7-segment display to reflect the value of "elapsed_time".
6. Finally, acknowledge that the interrupt has been handled by clearing
   the CAPT bit in the TCB1.INTFLAGS register.
   Refer to datasheet Section 22.5.5 Interrupt Flags on p. 260 for
   information on how to clear this bit.

NOTE: You may use display_hex() to display a number in hexadecimal on
the 7-segment display. This function accepts an unsigned 8-bit integer.

NOTE: As this interrupt is invoked every 1/64 of a second, the value in
"elapsed_time" will need to be divided by 4 before being displayed on
the 7-segment display (i.e., every 1/16 of a second).

You may find this equality useful:
    1/16 second = 4 * 1/64 second
*/

ISR(TCB1_INT_vect){
   if ((is_counting == 1)&&(elapsed_time < 1021)){
      elapsed_time += 1;
   }
   display_hex(elapsed_time/4);
   TCB1.INTFLAGS = TCB_CNTMODE0_bm;
}
/** CODE: Write your code for Ex 7.4 above this line. */
