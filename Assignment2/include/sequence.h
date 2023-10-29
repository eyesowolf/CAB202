#include <stdint.h>

void sequence_init(uint64_t SEED);
uint8_t sequence_next(void);
uint64_t get_seed(void);
