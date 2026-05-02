
#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>

#include "stm32h7xx.h"
#include "gpio.h"
#include "dds.h"
#include "dac.h"
#include "tim.h"
#include "dma.h"

#define BLOCK_SIZE 512

extern uint8_t dds_buffer_0[BLOCK_SIZE];
extern uint8_t dds_buffer_1[BLOCK_SIZE];
extern uint8_t dac_out_buffer_0[BLOCK_SIZE];
extern uint8_t dac_out_buffer_1[BLOCK_SIZE];

void clock_config(void);
void peripherals_init(void);
void delay_ms(uint32_t millisecs);
void SysTick_Handler(void);
void Error_Handler(void);

#endif
