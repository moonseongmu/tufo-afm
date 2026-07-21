#include "freq_sweep.h"

void set_sweep_settings(sweep_settings_t *settings, float start_freq, float end_freq, float step)
{
    settings->prev_amplitude = 0;
    settings->start_freq = start_freq;
    settings->end_freq = end_freq;
    settings->step_size = step;
}

void start_oscillations(sweep_settings_t *settings, dds_t *sin_dds, dds_t *cos_dds, uint32_t block_size, active_buffer_t *active_buffer,
    uint16_t *sin_buf_1, uint16_t *sin_buf_2, 
    uint16_t *cos_buf_1, uint16_t *cos_buf_2)
{
    //start timer and dma to adc and dac, interrupt calls when buffer filled/finished outputing
    block_transfer_init();
    //init cosdds with sweep starting frequency + starting phase 0
    cos_dds->tuning_word = freq_to_tuning_word(settings->start_freq, settings->clock_freq);
    cos_dds->phase_accumulator = 0;

    //init sindds with sweep starting frequency + starting phase 90
    sin_dds->tuning_word = freq_to_tuning_word(settings->start_freq, settings->clock_freq);
    sin_dds->phase_accumulator = 1073741824; //(2^32-1)/4

    block_transfer_start();
    
    for(int i = 0; i < 6; i++ )
    {
        fill_sin_cos_buffers(sin_dds, cos_dds, block_size, active_buffer, sin_buf_1, sin_buf_2, cos_buf_1, cos_buf_2);
    }
}

void fill_sin_cos_buffers(dds_t *sin_dds, dds_t *cos_dds, uint32_t block_size, active_buffer_t *active_buffer,
    uint16_t *sin_buf_1, uint16_t *sin_buf_2, 
    uint16_t *cos_buf_1, uint16_t *cos_buf_2)
{
    for (uint32_t i=0; i<block_size; i++)
    {
        dds_calculate(sin_dds);
        dds_calculate(cos_dds);
        switch (*active_buffer)
        {
            case buffer_1:
                cos_buf_1[i] = cos_dds->value;
                sin_buf_1[i] = sin_dds->value;
            case buffer_2:
                cos_buf_2[i] = cos_dds->value;
                sin_buf_2[i] = sin_dds->value;
        }
    }
}