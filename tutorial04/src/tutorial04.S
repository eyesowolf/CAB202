#include <avr/io.h> // Include register definitions

.section .init0     // Places code at the top of programme memory

.include "include/preamble.S"

// DO NOT EDIT ABOVE THIS LINE //

entry:

    // Ex 4.0
    //
    // Write assembly code below to advance the program counter such that
    // the next instruction executed is "mov r16, r13".
    //
    // Hint: Refer to the labels defined below.

    rjmp some_label_05

    // Write your code for Ex 4.0 above this line.

some_label_00:
    mov r16, r8
    rjmp end_ex40
some_label_01:
    mov r16, r9
    rjmp end_ex40
some_label_02:
    mov r16, r10
    rjmp end_ex40
some_label_03:
    mov r16, r11
    rjmp end_ex40
some_label_04:
    mov r16, r12
    rjmp end_ex40
some_label_05:
    mov r16, r13
    rjmp end_ex40
some_label_06:
    mov r16, r14
    rjmp end_ex40
some_label_07:
    mov r16, r15
    rjmp end_ex40

end_ex40:
    call avremu_r16out

    // Ex 4.1
    //
    // In the code included at the top of this program (by the .include
    // "include/preamble.S" assembler directive), several procedures have
    // been defined.
    //
    // Write assembly code below to call the procedure "some_procedure_03".

    call some_procedure_03

    // Write your code for Ex 4.1 above this line.
    lds r16, 0x3801
    call avremu_r16out

    // Ex 4.2
    //
    // We have defined a procedure "init_led_dp" below which is intended to
    // configure the pin that drives LED DS1-DP as an output, with the LED
    // initially off.
    //
    // Add the code required to achieve this functionality in the procedure
    // defined below.

    rjmp end_ex42 // Do not edit this line, it jumps over the procedure below.
                  // We will call this procedure later in the programme.

init_led_dp:
    // Write your code for Ex 4.2 below this line.

    ldi r19, PIN5_bm
    sts PORTB_OUT, r19
    sts PORTB_DIR, r19

    // Write your code for Ex 4.2 above this line.
    ret

end_ex42:
    rcall init_led_dp

    // Ex 4.3
    //
    // Write a procedure "toggle_led" in the space indicated below that
    // will toggle LED DS1-DP.

    rjmp end_ex43 // Do not edit this line, it jumps over the procedure below.
                  // We will call this procedure later in the programme.

toggle_led:
    // Write your code for Ex 4.3 below this line.

    sts PORTB_OUTTGL, r19

    // Write your code for Ex 4.3 above this line.
    ret

end_ex43:

    // Ex 4.4
    //
    // We have started writing a loop below that is intended to call the
    // procedure "some_procedure_08" a total of 7 times. Complete the
    // code for this loop.

    // Write your code for Ex 4.4 below this line.
    ldi r16, 7
    some_loop:
        call some_procedure_08
        dec r16
        cpi r16, 0
        brne some_loop

    // Write your code for Ex 4.4 above this line.
    lds r16, 0x3800
    call avremu_r16out

    // Ex 4.5
    //
    // We have started writing below a procedure called "delay" which is
    // intended to implement a busy delay.
    //
    // Write code to complete this procedure by adding instructions
    // that will take a total of 240 microseconds to execute.
    //
    // Tip: recall that the ATtiny1626 has a default system clock frequency
    // of 3.33 MHz.
    //
    // Note: If you have successfully completed Ex 4.2, 4.3, and 4.5,
    // the LED DS1-DP should flash 3 times.

    rjmp end_ex45 // Do not edit this line, it jumps over the procedure below.
                  // We will call this procedure later in the programme.

delay:
    // Write your code for Ex 4.5 below this line.
    adiw r24, 1
    cpi r24, 144
    brne delay
    // Write your code for Ex 4.5 above this line.
    ret

end_ex45:
    call flash_led
    ldi r16, 0xFF

// The code in main loop will execute indefinitely
main_loop:

    // Ex 4.6
    //
    // The code below reads the state of pushbutton S4.
    //
    // Add code such that LED DS1-DP is turned on whenever pushbutton S4
    // is pressed, and turned off whenever pushbutton S4 is released.
    //
    // Note that we have already enabled the pull-up resistor
    // for the corresponding pin for you.
    //
    // Tip: You will need to use branch or skip instructions.

    in r16, VPORTA_IN
    andi r16, PIN7_bm

    // Write your code for Ex 4.6 below this line.

    cpi r16, 0
    brne ex36_nonzero

    ex36_zero:

        sts PORTB_OUTCLR, r19
        rjmp end_ex36

    ex36_nonzero:

        sts PORTB_OUTSET, r19

    end_ex36:

    // Write your code for Ex 4.6 above this line.

// END OF TUTORIAL04 EXERCISES //
// DO NOT EDIT BELOW THIS LINE //
    rjmp main_loop
