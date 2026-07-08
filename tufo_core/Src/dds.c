#include <stdint.h>
#include <math.h>
#include "dds.h"

//initialise starting waveform phase
void dds_init(dds_t *dds, uint32_t start_phase)
{
    dds->phase_accumulator = start_phase;
}

//calculate next value of waveform 
void dds_calculate(dds_t *dds)
{
    dds->phase_accumulator += dds->tuning_word;
    dds->value = sine_lut[dds->phase_accumulator >> 20]; //truncate to 12 bits
}

//update tuning word
void dds_update_tuning_word(dds_t *dds, uint32_t tuning_word)
{
    dds->tuning_word = tuning_word;
}

//calculates necessary tuning word from desired frequency and dac output rate clock
uint32_t freq_to_tuning_word(float frequency, float clock_frequency)
{
    float tuning_word_float = (frequency/clock_frequency)*powf(2.0f, 32.0f);
    uint32_t tuning_word = (uint32_t) tuning_word_float;
    return tuning_word;
}

static const uint16_t sine_lut[4096];