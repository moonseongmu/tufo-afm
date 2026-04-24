#ifndef DAC_H
#define DAC_H

#include "stm32h7xx.h"
#include "main.h"

void dac_init(void);
void dac_update(uint8_t val);

#endif