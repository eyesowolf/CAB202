#include <stdint.h>

uint8_t STEP;
uint64_t MASK;
uint64_t STATE_LFSR;

void sequence_init(uint64_t SEED){
    MASK = 0xE2023CAB;
    STATE_LFSR = SEED;
}


uint8_t sequence_next(void)
{
    uint32_t BIT = STATE_LFSR & 0b1;
    STATE_LFSR >>= 1;
    if (BIT == 1){
        STATE_LFSR = STATE_LFSR ^ MASK;
    }
    STEP = STATE_LFSR & 0b11;
    return STEP;
}

uint64_t get_seed(void)
{
    return STATE_LFSR;
}