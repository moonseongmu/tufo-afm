#pragma once

#include "dds.h"
#include "interface.h"
#include "lockin.h"
#include "oscillator.h"
#include <stdbool.h>
#include <stdint.h>

typedef struct sweep_settings_t
{
    float start_freq;
    float end_freq;
    float step_size;
    float prev_amplitude;
    uint32_t clock_freq;
    bool sweep_complete;
} sweep_settings_t;

void fill_sin_cos_buffers(dds_t *sin_dds, dds_t *cos_dds, uint32_t block_size, active_buffer_t *active_buffer, uint16_t *sin_buf_1, uint16_t *sin_buf_2, uint16_t *cos_buf_1, uint16_t *cos_buf_2);
void start_oscillations(sweep_settings_t *settings, dds_t *sin_dds, dds_t *cos_dds);
void set_sweep_settings(sweep_settings_t *settings, float start_freq, float end_freq, float step);