#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <stdio.h>

#include "qutyserial.h"

/** Tutorial 08

INTRODUCTION:

In this week's tutorial you will be working with the TCA0 and
ADC0 peripherals. You will use these to control the brightness
of the 7-segment display, produce a tone from the buzzer, and
read the position of the potentiometer.

Interfacing with these hardware devices on the QUTy is a core
requirement for Assessment 2.
*/

/** EX: 8.0

TASK: Write a function named "pwm_init" which will configure
TCA0 to produce a

    3X0 Hz, 1Y % duty cycle output on the DISP EN net.

Where XY are the last two digits of your student number.

Your function should take no arguments and return no values.

EXAMPLE: If your student number were n12345678 then
you should configure TCA0 to produce a

    370 Hz, 18 % duty cycle output.
*/

// 380Hz, 16% duty

void pwm_init(void){
    PORTB.OUTSET = PIN1_bm;
    PORTB.DIRSET = PIN1_bm;
    TCA0.SINGLE.CTRLB=TCA_SINGLE_WGMODE_SINGLESLOPE_gc | TCA_SINGLE_CMP1EN_bm | TCA_SINGLE_CMP0EN_bm;
    TCA0.SINGLE.PER = 8775;
    TCA0.SINGLE.CMP1 = 1400;
    TCA0.SINGLE.CMP0 = 0;
    TCA0.SINGLE.CTRLA |= TCA_SINGLE_ENABLE_bm;
}

/** CODE: Write your code for Ex 8.0 above this line. */

/** EX: 8.1

TASK: Write a function named "adc_init" below which will configure
ADC0 in 8-bit single conversion mode.

The ADC should be configured to sample the voltage on the POT net,
be placed in free-running mode, and start sampling immediately.
*/

void adc_init(void){
    ADC0.CTRLA = ADC_ENABLE_bm;      // Enable ADC
    ADC0.CTRLB = ADC_PRESC_DIV2_gc;  // /2 clock prescaler 


    // Need 4 CLK_PER cycles @ 3.3 MHz for 1us, select VDD as ref
    ADC0.CTRLC = (4 << ADC_TIMEBASE_gp) | ADC_REFSEL_VDD_gc;
    ADC0.CTRLE = 64;                               // Sample duration of 64
    ADC0.CTRLF = ADC_FREERUN_bm;
    ADC0.MUXPOS = ADC_MUXPOS_AIN2_gc;              // Select AIN2 (potentiomenter R1)

    // 12-bit resolution, single-ended
    ADC0.COMMAND = ADC_MODE_SINGLE_8BIT_gc | ADC_START_IMMEDIATE_gc;
}

/** CODE: Write your code for Ex 8.1 above this line. */

int main(void)
{
    // Variable to store the result of the ADC conversion
    uint8_t result;

    serial_init();
    PORTA.DIRSET = PIN1_bm;
    PORTA.PIN7CTRL = PORT_PULLUPEN_bm;
    _delay_ms(3000); // 3 second delay

    /** EX: 8.2

    TASK: Call the two initialisation functions you have written above
    such that the TCA0 and ADC0 are enabled and operational.

    On completion of this exercise, the 7-segment display should show
    an 8 on the RHS that is initially bright, but dims after 3 seconds.

    You can then test your ADC configuration via the serial terminal
    using the instructions below.
    */
    pwm_init();
    adc_init();

    /** CODE: Write your code for Ex 8.2 above this line. */

    printf("Turn the potentiometer R1 fully counter-clockwise, then press S4.\n");
    while (VPORTA.IN & PIN7_bm); result = ADC0.RESULT0; printf("Ex 8.2.0: result = 0x%02X, expected = 0x00\n", result);
    _delay_ms(1000); printf("Turn the potentiometer R1 fully clockwise, then press S4.\n");
    while (VPORTA.IN & PIN7_bm); result = ADC0.RESULT0; printf("Ex 8.2.1: result = 0x%02X, expected = 0xFF\n", result);
    _delay_ms(1000); printf("Turn the potentiometer R1 to the half-way position, then press S4.\n");
    while (VPORTA.IN & PIN7_bm); result = ADC0.RESULT0; printf("Ex 8.2.2: result = 0x%02X, expected = ~0x80\n", result);

    // Main loop
    while (1)
    {
        /** EX: 8.3

        TASK: Write code below such that the position of the potentiometer
        controls the brightness of the 7-segment display in reverse.

        The display should be:
        - fully bright when the potentiometer is turned fully counter-clockwise
        - fully dim when the potentiometer is turned fully clockwise

        NOTE: ADC0.RESULT yields a value of 0 when the potentiometer is turned
        fully counter-clockwise, and a value of 255 when turned fully clockwise.

        You will need to reverse this range of values using a mathematical
        expression to achieve the desired functionality.

        HINT:

        1. Scale the 8-bit value from ADC0.RESULT to a value between
           0 and the TOP value of TCA0.
        2. Reverse the direction of the potentiometer by subtracting the
           scaled value from the TOP value of TCA0.

        Alternatively,

        1. Reverse the direction of the potentiometer by subtracting the
           8-bit value from ADC0.RESULT from 255.
        2. Scale the reversed value to a value between 0 and the TOP
           value of TCA0.

        TIP: Avoid floating-point arithmetic by performing integer operations.
        To ensure that you do not encounter integer overflow and loss of precision,
        perform operations in an appropriate order.
        */

       // set display brightness

        uint32_t compare;

        compare = (8775-(ADC0.RESULT*34.4));

        TCA0.SINGLE.CMP1BUF = compare;


        /** CODE: Write your code for Ex 8.3 above this line. */

        /** EX: 8.4

        TASK: Write code below such that the buzzer produces a 3X0 Hz tone
        when the potentiometer position is between 87.5% and 100%, where
        0% is fully CCW and 100% is fully CW.

        When the pot position is outside of this range the buzzer should be silent.

        The buzzer should be driven with a
        - 50 % duty cycle square wave when active
        - 0 % duty cycle square wave when inactive

        TIP: You will need to modify the code in pwm_init() to achieve this functionality.

        NOTE: The frequency specified above is the same as for Ex 8.0.
        */

        PORTB.OUTSET = PIN0_bm;
        PORTB.DIRSET = PIN0_bm;
        if (ADC0.RESULT >= 233){
            TCA0.SINGLE.CMP0BUF = 4387;
        } else {
            TCA0.SINGLE.CMP0BUF = 0;
        }

        /** CODE: Write your code for Ex 8.4 above this line. */
    }
}
