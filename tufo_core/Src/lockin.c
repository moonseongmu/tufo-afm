#include <stdint.h>
#include "lockin.h"
#include "interface.h"


void mult_array(uint16_t *src_1, uint16_t *src_2, uint32_t *dest, uint32_t block_size)
{
    for(uint32_t i = 0; i < block_size; i++)
    {
        dest[i] = src_1[i] * src_2[i];
    }
}

void low_pass_filter(uint32_t *src, uint32_t *dest, uint32_t block_size)
{
    low_pass_filter_impl();
}

void rect_to_polar(uint32_t *X, uint32_t *Y, float *modulus, float *phase, uint32_t block_size)
{
    rect_to_polar_impl();
}

void lock_in(uint16_t *sin_buffer, uint16_t *cos_buffer, uint16_t *signal_buffer, float *amplitude_buffer, float *phase_buffer, uint32_t block_size)
{
    uint32_t in_phase_buffer[block_size];
    uint32_t quadrature_buffer[block_size];

    uint32_t X_buffer[block_size];
    uint32_t Y_buffer[block_size];

    mult_array(cos_buffer, signal_buffer, in_phase_buffer, block_size);
    mult_array(sin_buffer, signal_buffer, quadrature_buffer, block_size);

    low_pass_filter(in_phase_buffer, X_buffer);
    low_pass_filter(quadrature_buffer, Y_buffer);

    rect_to_polar(X_buffer, Y_buffer, amplitude_buffer, phase_buffer, block_size);

}

