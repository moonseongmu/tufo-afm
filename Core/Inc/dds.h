#ifndef DDS_H
#define DDS_H

extern uint32_t tuning_word;
extern uint32_t phase_accumulator;
uint8_t dds(uint32_t tuning_word);
uint32_t freq_to_tuning_word(float frequency, float clock_frequency);
static const uint8_t sine_lut[4096];
#endif