#include "tim.h"
#include "main.h"

void tim8_init(void){
    //apb1 timer clock set to 200MHz
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM8EN); //enable timer 8
    SET_BIT(TIM8->CR1, TIM_CR1_ARPE); //arr preload enable
    WRITE_REG(TIM8->PSC, 0); //set perscaler to 0
    WRITE_REG(TIM8->ARR, 200-1); //overflow at 200 for 1MHz update frequency
    MODIFY_REG(TIM8->CR2, TIM_CR2_MMS, TIM_CR2_MMS_1); //set update as trgo
    SET_BIT(TIM8->CR1, TIM_CR1_CEN); //enable counter
}

