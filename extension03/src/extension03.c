/** CODE: Include any necessary header files and macro definitions here. */

/** EX: E3.0

In this week's tutorial, we used some functions from the libraries
"qutyio.h" and <stdio.h> to output data via the serial interface.
This can be a useful tool for debugging your programme.

To use the serial interface you first need to initialise the
required hardware by calling serial_init(); this only needs to
be done once at the beginning of your programme.

After this, you can use the function printf() from
<stdio.h> to output formatted strings via the serial interface.

You will need to use printf() in few different ways in this
extension exercise:

    printf("foo")     - prints the word 'foo' to the serial output.
    printf("bar")     - prints the word 'bar' to the serial output.
    printf(" ")       - prints a space to the serial output.
    printf("%02X", x) - prints the 8-bit integer 'x' to the
                        serial output, formatted as two uppercase
                        hexadecimal digits.
    printf("\n")      - prints a new line to the serial output.

Note that the above cases may also be combined.

TASK: Your task is to write C code to do the following:

1. Include "qutyio.h" and <stdio.h>, and initialise the serial
   interface using serial_init().
2. Create a variable "state" to store your student number as
   a decimal value. You should use a fixed-width integer type
   from the <stdint.h> header file.
3. Iterate through all the numbers from 0 to 255 in sequence,
   and for each number, perform the following steps:
   a. Take the bitwise XOR of the number with the variable "state",
      storing the result back into "state".
   b. Rotate right the bits in "state" at least one time, and until
      the LSB of "state" is a zero. If there are no cleared bits in
      "state" do nothing.
   c. Print the least significant two bytes of "state" to the serial
      output as four uppercase hexadecimal digits, followed by a space.
      The prefix "0x" is not required.
   d. Inspect bits 11-4 of "state" (where bit 0 is the LSB).
      - If the most significant nibble of this byte, represented as
        a hexadecimal digit, matches the second last digit of your
        student number, represented as a decimal digit,
        print the word "foo" to the serial output.
      - If the least significant nibble of this byte, represented as
        a hexadecimal digit, matches the final digit of your
        student number, represented as a decimal digit,
        print the word "bar" to the serial output.
      - If both match, print "foobar".
   e. Print a newline character to the serial output.
4. After step 3, your programme should have printed 256 lines to the
   serial output.

Programme execution should now proceed to the infinite loop
without producing any further output.

EXAMPLES:

    Assume for all examples below the student number is n1234 5678

    Assume that after step 4b "state" holds the value 0xE00B C614
        The programme should print the line: C614

    Assume that after step 4b "state" holds the value 0xD76F 77F0
        The programme should print the line: 77F0 foo

    Assume that after step 4b "state" holds the value 0x7802 F184
        The programme should print the line: F184 bar

    Assume that after step 4b "state" holds the value 0xAFB6 F784
        The programme should print the line: F784 foobar
*/

// #include and #define preprocessor directives should be
// placed at the top of your source files, in the global scope.
// Including certain header files within functions may cause the
// compiler to fail.

#include <stdio.h>
#include "qutyio.h"

int main(void)
{
    /** CODE: Write your code for Ex E3.0 below this line. */
   serial_init();
   uint32_t state = 11150386;
   for(int i=0;i<256;i++){
      state ^= i;
      if (state != 0xFFFF){
         if ((state & 0b1) == 1){
            state >>= 1;
            state |= 0x80000000;
         } else {
            state >>= 1;
         }
         
         while((state & 0b1) != 0){
            state >>= 1;
            state |= 0x80000000;
         }
      }
      printf("%04hhX ", state & 0xFFFF);
      if ((state & 0xF00) == 0x800){
         printf("foo");
      }
      if ((state & 0xF0) == 0x60){
         printf("bar");
      }
      printf("\n");
   }
    /** CODE: Write your code for Ex E3.0 above this line. */

    // END OF EXTENSION03 EXERCISES //
    // DO NOT EDIT BELOW THIS LINE  //

    while (1)
        ; // Loop indefinitely
}
