#pragma once

#define BLOCK_SIZE 512

uint16_t sin_buffer_1[BLOCK_SIZE];
uint16_t sin_buffer_2[BLOCK_SIZE];
uint16_t cos_buffer_1[BLOCK_SIZE];
uint16_t cos_buffer_2[BLOCK_SIZE];
uint16_t adc_in_buffer_1[BLOCK_SIZE];
uint16_t adc_in_buffer_2[BLOCK_SIZE];

void mult_array(uint16_t *src_1, uint16_t *src_2, uint32_t *dest, uint32_t block_size);
void low_pass_filter(uint32_t *src, uint32_t *dest, uint32_t block_size);
void rect_to_polar(uint32_t *X, uint32_t *Y, float *modulus, float *phase, uint32_t block_size);
void lock_in(uint16_t *sin_buffer, uint16_t *cos_buffer, uint16_t *signal_buffer, float *amplitude_buffer, float *phase_buffer, uint32_t block_size);
