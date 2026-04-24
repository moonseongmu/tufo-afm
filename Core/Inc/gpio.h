
#ifndef GPIO_H
#define GPIO_H

#include "stm32h7xx.h"
#include "main.h"

enum GPIO_Pin{
    GPIO_Pin_0 = 1, GPIO_Pin_1 = 2, GPIO_Pin_2 = 4, GPIO_Pin_3 = 8,
    GPIO_Pin_4 = 16, GPIO_Pin_5 = 32, GPIO_Pin_6 = 64, GPIO_Pin_7 = 128,
    GPIO_Pin_8 = 256, GPIO_Pin_9 = 512, GPIO_Pin_10 = 1024, GPIO_Pin_11 = 2048,
    GPIO_Pin_12 = 4096, GPIO_Pin_13 = 8192, GPIO_Pin_14 = 16384, GPIO_Pin_15 = 32768
};
void gpio_init(void);
void gpio_clear_pin(GPIO_TypeDef* GPIOx, enum GPIO_Pin Pin);
void gpio_set_pin(GPIO_TypeDef* GPIOx, enum GPIO_Pin Pin);
void gpio_toggle_pin(GPIO_TypeDef* GPIOx, enum GPIO_Pin Pin);

#endif

