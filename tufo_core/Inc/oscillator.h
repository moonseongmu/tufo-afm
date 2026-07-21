#pragma once

#define BLOCK_SIZE 512

typedef enum active_buffer_t
{
    buffer_1,
    buffer_2
} active_buffer_t; //buffer used for calculations, not currently being filled by adc/being output by dac

uint16_t sin_buffer_1[BLOCK_SIZE];
uint16_t sin_buffer_2[BLOCK_SIZE];
uint16_t cos_buffer_1[BLOCK_SIZE];
uint16_t cos_buffer_2[BLOCK_SIZE];
uint16_t adc_in_buffer_1[BLOCK_SIZE];
uint16_t adc_in_buffer_2[BLOCK_SIZE];
float amplitude_buffer_1[BLOCK_SIZE];
float amplitude_buffer_2[BLOCK_SIZE];
float phase_buffer_1[BLOCK_SIZE];
float phase_buffer_2[BLOCK_SIZE];