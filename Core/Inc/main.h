
#ifndef __MAIN_H
#define __MAIN_H

#include <stdint.h>

#include "stm32h7xx.h"

void clock_config(void);
void peripherals_init(void);
void gpio_init(void);
void tim14_init(void);
void delay_ms(uint32_t millisecs);
void SysTick_Handler(void);
void Error_Handler(void);

#endif
