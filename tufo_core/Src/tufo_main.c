#include "tufo_main.h"
#include "dds.h"
#include "freq_sweep.h"
#include "oscillator.h"
#include "stm32h723xx.h"


typedef enum state_t
{
    STATE_IDLE,
    STATE_SWEEP_INIT,
    STATE_FREQ_SWEEP,
    STATE_SWEEP_STOP,
    STATE_ACQUIRE
} state_t;


void tufo_main(void)
{

    state_t state = STATE_IDLE;

    sweep_settings_t sweep_settings = {.sweep_complete = false};
    
    active_buffer_t active_buffer = buffer_1;

    bool buffers_swapped = false;

    dds_t sin_dds;
    dds_t cos_dds;

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

    while(1)
    {
        switch(state)
        {
            case STATE_IDLE:

                if(buffers_swapped == true)
                {
                    state = STATE_FREQ_SWEEP;
                }
                break;

            case STATE_SWEEP_INIT:
                set_sweep_settings(&sweep_settings, 32677, 32679, 0.1);
                start_oscillations(&sweep_settings, &sin_dds, &cos_dds, BLOCK_SIZE, active_buffer, sin_buffer_1, sin_buffer_2, cos_buffer_1, cos_buffer_2);
                sweep_settings.sweep_complete = false;
                state = STATE_IDLE;
                break;

            case STATE_FREQ_SWEEP:
                break;

            case STATE_SWEEP_STOP:
                break;
            case STATE_ACQUIRE:
                break;

        }
    }
}