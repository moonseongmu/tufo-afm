#pragma once

#include "main.h"
#include <stdint.h>

typedef struct 
{
    uint32_t phase_accumulator;
    uint32_t tuning_word;
    uint16_t value;
} dds_t;


void dds_init(uint32_t start_phase);
uint16_t dds_update(uint32_t tuning_word);
uint32_t freq_to_tuning_word(float frequency, float clock_frequency);

static const uint16_t sine_lut[4096];