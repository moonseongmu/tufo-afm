#include "tufo_main.h"

typedef enum state_t
{
    STATE_IDLE,
    STATE_SWEEP_INIT,
    STATE_FREQ_SWEEP,
    STATE_SWEEP_STOP,
    STATE_ACQUIRE
} state_t;

typedef enum command_t
{
    NONE,
    COMMAND_START_SWEEP,
    COMMAND_START_ACQUISITION
} command_t;


void tufo_main(void)
{

    state_t state = STATE_IDLE;
    command_t command = NONE;

    sweep_settings_t sweep_settings = {.sweep_complete = false};

    oscillator_t oscillator = {.init_counter = 0, .buffers_swapped = false, 
                                .active_buffer = buffer_1};

    while(1)
    {
        switch(state)
        {
            case STATE_IDLE: //TODO: implement idle case

                if (command == COMMAND_START_SWEEP)
                {
                    state = STATE_SWEEP_INIT;
                }
                if(oscillator.buffers_swapped == true && sweep_settings.sweep_complete == false)
                {
                    state = STATE_FREQ_SWEEP;
                } else if(oscillator.buffers_swapped == true && sweep_settings.sweep_complete == true)
                {
                    state = STATE_SWEEP_STOP;
                }
                break;

            case STATE_SWEEP_INIT:
                set_sweep_settings(&sweep_settings, 32677, 32679, 0.1, 0.1);
                start_oscillations(&sweep_settings, &oscillator, BLOCK_SIZE);
                sweep_settings.sweep_complete = false;
                state = STATE_IDLE;
                break;

            case STATE_FREQ_SWEEP:
                continue_oscillations(&sweep_settings, &oscillator, BLOCK_SIZE);
                break;

            case STATE_SWEEP_STOP:
                break;

            case STATE_ACQUIRE:
                break;

        }
    }
}