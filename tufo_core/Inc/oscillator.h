#pragma once

#define BLOCK_SIZE 512

typedef enum active_buffer_t
{
    buffer_1,
    buffer_2
} active_buffer_t; //buffer used for calculations, not currently being filled by adc/being output by dac

