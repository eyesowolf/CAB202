#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>
#include "adc.h"
#include "buttons.h"
#include "buzzer.h"
#include "display.h"
#include "pwm.h"
#include "sequence.h"
#include "spi.h"
#include "timers.h"
#include "uart.h"

typedef enum {  
    GAME_START,
    PLAY_SEQUENCE,
    SEQUENCE_WAIT,
    SEQUENCE_INPUT_START,
    SEQUENCE_INPUT,
    SEQUENCE_SUCCESS,
    SEQUENCE_FAIL,
    SHOW_SCORE
} GAME_STATE;

void init (void);
void Pos1(void);
void Pos2(void);
void Pos3(void);
void Pos4(void);
void CLEAR(void);
void delay(void);
void delay_full(void);
void display_sequence(uint8_t step);
uint8_t check_input(void);
void detect_lift(void);
void display_score(uint32_t n);

void test_output(void);
void test_disp(void);
void test_nums(void);

uint8_t step;
uint8_t pb_state;
uint8_t pb_state_r;
uint64_t seed = 0x11150386;

int main(void)
{
    GAME_STATE state = PLAY_SEQUENCE;
    uint32_t score = 0;
    uint32_t steps = 0;
    timer = 0;
    init();



    while(1){
        PLAYBACK_DELAY = (ADC0.RESULT*6.863)+250;
        //test_nums();
        //test_output();
        //test_disp();


        switch(state){
            case GAME_START:
                sequence_init(seed);
                state = PLAY_SEQUENCE;
                steps = 0;
                break;
            case PLAY_SEQUENCE:
                if (steps <= score){
                    display_sequence(sequence_next());
                    steps++;
                    delay();
                    state = SEQUENCE_WAIT;
                } else {state = SEQUENCE_INPUT_START;}
                break;
            case SEQUENCE_WAIT:
                CLEAR();
                delay();
                state = PLAY_SEQUENCE;
                break;
            case SEQUENCE_INPUT_START:
                sequence_init(seed);
                steps = 0;
                state = SEQUENCE_INPUT;
                break;
            case SEQUENCE_INPUT:
                if (steps <= score){
                    uint8_t button = check_input();
                    display_sequence(button);
                    timer = 0;
                    detect_lift();
                    steps++;
                    if (button != sequence_next()){
                        state = SEQUENCE_FAIL;
                    } else {state = SEQUENCE_INPUT;}
                } else {
                    delay();
                    state = SEQUENCE_SUCCESS;
                }
                break;
            case SEQUENCE_SUCCESS:
                update_display(DISP_SUCCESS,DISP_SUCCESS);
                delay_full();
                CLEAR();
                score++;
                state = GAME_START;
                break;
            case SEQUENCE_FAIL:
                update_display(DISP_FAIL,DISP_FAIL);
                delay_full();
                CLEAR();
                state = SHOW_SCORE;
                break;
            case SHOW_SCORE:
                display_score(score);
                delay_full();
                CLEAR();
                score = 0;
                seed = get_seed();
                state = GAME_START;
                break;
        }

    }
}

void display_sequence(uint8_t step){
    switch(step&0b11){
        case 0b00:
            Pos1();
            break;
        case 0b01:
            Pos2();
            break;
        case 0b10:
            Pos3();
            break;
        case 0b11:
            Pos4();
            break;
    }
}

uint8_t check_input(void){
    while(1){
        pb_state_r = pb_state;
        pb_state = pb_debounced_state;
        if ((pb_state ^ pb_state_r) & ~pb_state){
            switch(pb_state>>4){
                case 0b1110:
                    return 0b00;
                    break;
                case 0b1101:
                    return 0b01;
                    break;
                case 0b1011:
                    return 0b10;
                    break;
                case 0b0111:
                    return 0b11;
                    break;
            }
        } 
    }
}

void detect_lift(void){
    while(1){
        pb_state_r = pb_state;
        pb_state = pb_debounced_state;
        if ((pb_state_r ^ pb_state) & pb_state){
            while(timer<(PLAYBACK_DELAY>>1)){
            }
            CLEAR();
            break;
        }
    }
}


void Pos1(void){
    update_display(DISP_VERT_BAR_L,DISP_OFF);
    buzzer_on(0);
}

void Pos2(void){
    update_display(DISP_VERT_BAR_R,DISP_OFF);
    buzzer_on(1);
}
void Pos3(void){
    update_display(DISP_OFF,DISP_VERT_BAR_L);
    buzzer_on(2);
}
void Pos4(void){
    update_display(DISP_OFF,DISP_VERT_BAR_R);
    buzzer_on(3);
}

void CLEAR(void){
    update_display(DISP_OFF,DISP_OFF);
    buzzer_off();
}

void delay(void){
    PLAYBACK_DELAY = (ADC0.RESULT*6.863)+250;
    timer=0;
    while(timer<(PLAYBACK_DELAY>>1)){
    }
}

void delay_full(void){
    PLAYBACK_DELAY = (ADC0.RESULT*6.863)+250;
    timer=0;
    while(timer<PLAYBACK_DELAY){    }
}

void display_score(uint32_t n){
    uint16_t digits = log10(n);
    uint8_t disp_left = DISP_OFF;
    uint8_t disp_right = DISP_OFF;
    switch(n%10){
        case 0:
            disp_right = DISP_0;
            break;
        case 1:
            disp_right = DISP_1;
            break;
        case 2:
            disp_right = DISP_2;
            break;
        case 3:
            disp_right = DISP_3;
            break;
        case 4:
            disp_right = DISP_4;
            break;
        case 5:
            disp_right = DISP_5;
            break;
        case 6:
            disp_right = DISP_6;
            break;
        case 7:
            disp_right = DISP_7;
            break;
        case 8:
            disp_right = DISP_8;
            break;
        case 9:
            disp_right = DISP_9;
            break;
    }
    uint32_t digit2 = n/10;
    switch(digit2%10){
        case 0:
        disp_left = DISP_0;
        break;
    case 1:
        disp_left = DISP_1;
        break;
    case 2:
        disp_left = DISP_2;
        break;
    case 3:
        disp_left = DISP_3;
        break;
    case 4:
        disp_left = DISP_4;
        break;
    case 5:
        disp_left = DISP_5;
        break;
    case 6:
        disp_left = DISP_6;
        break;
    case 7:
        disp_left = DISP_7;
        break;
    case 8:
        disp_left = DISP_8;
        break;
    case 9:
        disp_left = DISP_9;
        break;
    }
    if (n < 10) {disp_left = DISP_OFF;}
    update_display(disp_left,disp_right);
}

void init (void){
    adc_init();
    button_init();
    spi_init();
    uart_init();
    timer_init();
    pwm_init();
    sequence_init(0x11150386);
    buzzer_init();
}


// TESTS


void test_output(void){
    Pos1();
    delay();
    Pos2();
    delay();
    Pos3();
    delay();
    Pos4();
    delay();
    delay();
}

void test_disp(void){
    update_display(DISP_OFF,DISP_A);
    delay();
    update_display(DISP_OFF,DISP_B);
    delay();
    update_display(DISP_OFF,DISP_C);
    delay();
    update_display(DISP_OFF,DISP_D);
    delay();
    update_display(DISP_OFF,DISP_E);
    delay();
    update_display(DISP_OFF,DISP_F);
    delay();
    update_display(DISP_OFF,DISP_G);
    delay();
    delay();
}

void test_nums(void){
    update_display(DISP_0,DISP_1);
    delay();
    update_display(DISP_1,DISP_2);
    delay();
    update_display(DISP_2,DISP_3);
    delay();
    update_display(DISP_3,DISP_4);
    delay();
    update_display(DISP_4,DISP_5);
    delay();
    update_display(DISP_5,DISP_6);
    delay();
    update_display(DISP_6,DISP_7);
    delay();
    update_display(DISP_7,DISP_8);
    delay();
    update_display(DISP_8,DISP_9);
    delay();
    update_display(DISP_9,DISP_0);
    delay();
}