#include "gpio.h"


void gpio_clear_pin(GPIO_TypeDef* GPIOx, enum GPIO_Pin Pin){
    SET_BIT(GPIOx->BSRR, Pin << GPIO_BSRR_BR0_Pos);
}

void gpio_set_pin(GPIO_TypeDef* GPIOx, enum GPIO_Pin Pin){
    SET_BIT(GPIOx->BSRR, Pin << GPIO_BSRR_BS0_Pos);
}

void gpio_toggle_pin(GPIO_TypeDef* GPIOx, enum GPIO_Pin Pin){
    if(READ_BIT(GPIOx->ODR, Pin << GPIO_ODR_OD0_Pos)){ //if pin is set
        gpio_clear_pin(GPIOx, Pin);
    } else {
        gpio_set_pin(GPIOx, Pin);
    }
    
}