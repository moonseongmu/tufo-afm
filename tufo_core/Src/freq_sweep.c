#include "freq_sweep.h"

float mean(float *array, uint32_t size)
{
    float sum = 0;
    for (uint32_t i = 0; i < size; i++)
    {
        sum += array[i];
    }
    return sum/size;
}

void set_sweep_settings(sweep_settings_t *settings, float start_freq, float end_freq, float step, float max_epsilon)
{
    settings->prev_amplitude = 0;
    settings->start_freq = start_freq;
    settings->end_freq = end_freq;
    settings->step_size = step;
    settings->max_epsilon = max_epsilon;
}

void start_oscillations(sweep_settings_t *settings, 
    dds_t *sin_dds, dds_t *cos_dds, 
    uint32_t block_size, active_buffer_t active_buffer, uint32_t *counter, bool buffers_swapped,
    uint16_t *sin_buf_1, uint16_t *sin_buf_2, 
    uint16_t *cos_buf_1, uint16_t *cos_buf_2, 
    uint16_t *sig_buf_1, uint16_t *sig_buf_2,
    float *ampl_buf_1, float *ampl_buf_2, 
    float *phase_buf_1, float *phase_buf_2)
{
    //start timer and dma to adc and dac, interrupt calls when buffer filled/finished outputing
    block_transfer_init();
    //init cosdds with sweep starting frequency + starting phase 0
    cos_dds->tuning_word = freq_to_tuning_word(settings->start_freq, settings->clock_freq);
    cos_dds->phase_accumulator = 0;

    //init sindds with sweep starting frequency + starting phase 90
    sin_dds->tuning_word = freq_to_tuning_word(settings->start_freq, settings->clock_freq);
    sin_dds->phase_accumulator = 1073741824; //(2^32-1)/4 for 90* initial starting offset phase
    settings->current_freq = settings->start_freq;

    block_transfer_start();
    float amplitude_avg = 0.0f;
    
    while(buffers_swapped == true && *counter < 6)
    {
        switch(active_buffer)
        {
            case buffer_1:
                lock_in(sin_buf_1, cos_buf_1, sig_buf_1, ampl_buf_1, phase_buf_1, block_size);
                amplitude_avg = mean(ampl_buf_1, block_size);
                fill_sin_cos_buffers(sin_dds, cos_dds, block_size, sin_buf_1, cos_buf_1);
                break;
            case buffer_2:
                lock_in(sin_buf_2, cos_buf_2, sig_buf_2, ampl_buf_2, phase_buf_2, block_size);
                amplitude_avg = mean(ampl_buf_2, block_size);
                fill_sin_cos_buffers(sin_dds, cos_dds, block_size, sin_buf_2, cos_buf_2);
                break;
        }
        settings->prev_amplitude = amplitude_avg;
        *counter += 1;
        buffers_swapped = false;
    }
}


void continue_oscillations(sweep_settings_t *settings, 
    dds_t *sin_dds, dds_t *cos_dds, 
    uint32_t block_size, active_buffer_t active_buffer, bool buffers_swapped,
    uint16_t *sin_buf_1, uint16_t *sin_buf_2, 
    uint16_t *cos_buf_1, uint16_t *cos_buf_2, 
    uint16_t *sig_buf_1, uint16_t *sig_buf_2,
    float *ampl_buf_1, float *ampl_buf_2, 
    float *phase_buf_1, float *phase_buf_2)
{
    float amplitude_avg = 0.0f;
    switch(active_buffer)
    {
        case buffer_1:
            lock_in(sin_buf_1, cos_buf_1, sig_buf_1, ampl_buf_1, phase_buf_1, block_size);
            amplitude_avg = mean(ampl_buf_1, block_size);
            fill_sin_cos_buffers(sin_dds, cos_dds, block_size, sin_buf_1, cos_buf_1);
            break;
        case buffer_2:
            lock_in(sin_buf_2, cos_buf_2, sig_buf_2, ampl_buf_2, phase_buf_2, block_size);
            amplitude_avg = mean(ampl_buf_2, block_size);
            fill_sin_cos_buffers(sin_dds, cos_dds, block_size, sin_buf_2, cos_buf_2);
            break;
    }
    
    if(fabsf(amplitude_avg - settings->prev_amplitude) < settings->max_epsilon)
    {
        //amplitude has stabilised, move tuning word to next step
        settings->current_freq += settings->step_size;
        sin_dds->tuning_word = freq_to_tuning_word(settings->current_freq, settings->clock_freq);
        cos_dds->tuning_word = freq_to_tuning_word(settings->current_freq, settings->clock_freq);
    }
    settings->prev_amplitude = amplitude_avg;
    buffers_swapped = false;
}

void fill_sin_cos_buffers(dds_t *sin_dds, dds_t *cos_dds, uint32_t block_size, uint16_t *sin_buf, uint16_t *cos_buf)
{
    for (uint32_t i=0; i<block_size; i++)
    {
        dds_calculate(sin_dds);
        dds_calculate(cos_dds);
            cos_buf[i] = cos_dds->value;
            sin_buf[i] = sin_dds->value;
    }
}


