#include "freq_sweep.h"
#include "dds.h"
#include "interface.h"
#include "lockin.h"
#include <stdbool.h>

struct sweep_settings
{
    float start_freq;
    float end_freq;
    float step_size;
    float prev_amplitude;
};

void set_sweep_settings(sweep_settings *settings, float start_freq, float end_freq, float step)
{
    settings->prev_amplitude = 0;
    settings->start_freq = start_freq;
    settings->end_freq = end_freq;
    settings->step_size = step;
}

void start_sweep(sweep_settings *settings)
{
    dds_t *dds;
    block_transfer_init();
    block_transfer_start();
    dds_init(dds, 0);
    bool sweep_done = false;

    while(sweep_done == false)
    {
        switch(active)
    }

}