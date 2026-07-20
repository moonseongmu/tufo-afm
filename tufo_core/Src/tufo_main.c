#include "tufo_main.h"

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

    bool buffers_swapped = false;

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
                start_oscillations(start_freq_word);
                sweep_settings.sweep_complete = false;



            case STATE_FREQ_SWEEP:
                break;

        }
    }
}