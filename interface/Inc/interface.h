#pragma once

#include <stdint.h>


//lockin.c
void low_pass_filter_impl();
void rect_to_polar_impl();


void timer_1MHz_init(void); //setup 1MHz interrupt rate timer
void timer_1MHz_ISR(void); //ouptut new tuning fork dac value and read in new tuning fork adc value, calculate new dds tuning word using pid loop, swap buffers if needed


void dac_init(void); //setup dac
void dac_update(uint16_t value); //send new value to dac

void adc_init(void); //setup adc
void adc_read(void); //read new value from adc