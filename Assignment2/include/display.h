#ifndef DISPLAY_H
#define DISPLAY_H 1

#include <stdint.h>

#define DISP_A 0b01011111
#define DISP_B 0b01101111
#define DISP_C 0b01111011
#define DISP_D 0b01111101
#define DISP_E 0b01111110
#define DISP_F 0b00111111
#define DISP_G 0b01110111

#define DISP_VERT_BAR_L (DISP_F & DISP_E)
#define DISP_VERT_BAR_R (DISP_B & DISP_C)
#define DISP_FAIL DISP_G
#define DISP_SUCCESS 0b00000000

#define DISP_1 (DISP_B & DISP_C)
#define DISP_2 (DISP_A & DISP_B & DISP_G & DISP_E & DISP_D)
#define DISP_3 (DISP_B & DISP_C & DISP_A & DISP_G & DISP_D)
#define DISP_4 (DISP_B & DISP_C & DISP_F & DISP_G)
#define DISP_5 (DISP_A & DISP_F & DISP_G & DISP_C & DISP_D)
#define DISP_6 (DISP_F & DISP_E & DISP_A & DISP_G & DISP_C & DISP_D)
#define DISP_7 (DISP_B & DISP_C & DISP_A)
#define DISP_8 (DISP_SUCCESS)
#define DISP_9 (DISP_B & DISP_C & DISP_A & DISP_F & DISP_G & DISP_D)
#define DISP_0 (DISP_F & DISP_E & DISP_B & DISP_C & DISP_A & DISP_D)

#define DISP_OFF 0b01111111

#define DISP_LHS (1 << 7)

extern volatile uint8_t left_byte;
extern volatile uint8_t right_byte;

void update_display(const uint8_t left, const uint8_t right);

#endif
