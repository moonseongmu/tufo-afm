#include <stdint.h>
#include <math.h>
#include "dds.h"

uint32_t phase_accumulator = 0;
uint32_t tuning_word = 0;

void dds_init(uint32_t start_phase)
{

}

uint16_t dds_update(uint32_t tuning_word)
{
    phase_accumulator += tuning_word;
    uint16_t index = phase_accumulator >> 20; //truncate to 12 bits
    return sine_lut[index];
}

uint32_t freq_to_tuning_word(float frequency, float clock_frequency)
{
    float tuning_word_float = (frequency/clock_frequency)*powf(2.0f, 32.0f);
    uint32_t tuning_word = (uint32_t) tuning_word_float;
    return tuning_word;
}

static const uint16_t sine_lut[4096];