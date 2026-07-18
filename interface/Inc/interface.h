#pragma once

#include <stdint.h>

void dac_init(void);
void dac_update(uint16_t value);

//lockin.c
void low_pass_filter_impl();
void rect_to_polar_impl();