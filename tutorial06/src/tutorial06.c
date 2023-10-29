#include <avr/io.h>
#include <stdint.h>
#include <stdio.h>

#include "qutyio.h"

/** Tutorial 06

INTRODUCTION:

In this week's tutorial you will be writing C code to implement
a pseudo-random number generator. This will be of particular
relevance to your Assessment 2 project. You may like to review
the Assessment 2 task description and specification so that you
have an understanding of the project context and how this week's
tutorial exercise might contribute towards the functional
requirements of the project.
*/

/** EX: 6.0

TASK: Define a global variable called "state" with the type of
an unsigned 32-bit integer.

Initialise "state" with a value equal to your student number,
where each decimal digit in your student number represents
a hexadecimal literal.

EXAMPLE: If your student number was n12345678 then you should
assign the hex value 0x12345678 to "state".

Once you have defined this variable uncomment the first printf()
statement in main() such that its value is printed.
*/

uint32_t state = 0x11150386;


/** CODE: Write your code for Ex 6.0 above this line. */

/** EX: 6.1

TASK: Write the function prototype for a function called "next"
which takes no parameters and returns no result.
*/

void next(void);

/** CODE: Write your code for Ex 6.1 above this line. */

/** EX: 6.2

TASK: Write a function called "print_rand" which returns no result
and takes, as a single argument, a pointer to an unsigned 32-bit
integer.

The function should inspect the least significant two bits
of the integer pointed to by the argument, and depending on
the value of the bits, execute one of the following function
calls:

    0b00 (0): putchar('1');
    0b01 (1): putchar('2');
    0b10 (2): putchar('3');
    0b11 (3): putchar('4');

Once you have written this function uncomment the second printf()
statement in main() such that its operation can be tested.
*/

void print_rand(uint32_t *a){
    switch(*a & 0b11){
        case 0b00: 
            putchar('1');
            break;
        case 0b01:
            putchar('2');
            break;
        case 0b10:
            putchar('3');
            break;
        case 0b11:
            putchar('4');
            break;
    }
}

/** CODE: Write your code for Ex 6.2 above this line. */

/** EX: 6.3

TASK: Complete the implementation for the next() function.

next() should:

1. Right shift the bits in "state" by 1 bit position.
2. If the bit shifted out of state was set (1), take the XOR
   of "state" with 0xA8E831E0 and store the result in "state".

Once you have written this function uncomment the third printf()
statement in main() such that its operation can be tested.
*/

void next(void)
{
    /** CODE: Write your code for Ex 6.3 within this function. */
    if ((state & 0b1) == 0b1){
        state >>= 1;
        state ^= 0xA8E831E0;
    } else {
        state >>= 1;
    }
}

int main(void)
{
    serial_init();

    /** TODO: Uncomment the line below when Ex 6.0 is complete. */
    printf("Ex 6.0: state = 0x%08lX\n", state);

    /** TODO: Uncomment the line below when Ex 6.2 is complete. */
    uint32_t test = 0b1100; printf("Ex 6.2: output = "); print_rand(&test); test >>= 1; print_rand(&test); test >>= 1; print_rand(&test); test >>= 1; print_rand(&test); printf("\n");

    /** TODO: Uncomment the line below when Ex 6.3 is complete. */
    next(); printf("Ex 6.3: state = 0x%08lX", state); next(); next(); next(); next(); printf(", state = 0x%08lX\n", state);

    /** EX: 6.4

    The variable "state" together with the function next()
    you have written above implement a linear-feedback shift
    register, which can produce a pseudorandom number sequence.
    We seeded this sequence (i.e., set the initial value) with
    your student number at the start of the programme. The tests
    above have already made a few calls to next() so you should
    expect the value currently stored in "state" to be different
    from the initial seed.

    The function print_rand() you wrote above can be used to
    operate on the variable "state" to print a digit in the
    range 1-4.

    TASK: Write code below to print the next 32 digits (from 1-4)
    derived from this pseudorandom number sequence using
    next() and print_rand().

    All the digits should be printed on a single line without spaces.

    NOTE: You should call next() to advance "state" prior to printing
    the first digit.

    TIP: You will likely want to use a loop to complete the required
    number of repeated function calls.

    TIP: Recall that the unary operator "&" can be used to get a
    reference (pointer) to some data.
    */

    printf("Ex 6.4: ");
    /** CODE: Write your code for Ex 6.4 below this line. */
    for(int i = 0; i < 32; i++){
        next();
        print_rand(&state);
    }
    /** CODE: Write your code for Ex 6.4 above this line. */
    printf("\n");

    // END OF TUTORIAL06 EXERCISES //
    // DO NOT EDIT BELOW THIS LINE //

    while (1)
        ; // Loop indefinitely
}



