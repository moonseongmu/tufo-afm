
#ifndef __MAIN_H
#define __MAIN_H

#include <stdint.h>

#include "stm32h7xx.h"
#include "gpio.h"
#include "dds.h"
#include "dac.h"
#include "tim.h"

void clock_config(void);
void peripherals_init(void);
void delay_ms(uint32_t millisecs);
void SysTick_Handler(void);
void Error_Handler(void);

#endif
