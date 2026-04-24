#include "tim.h"
#include "dds.h"
#include "dac.h"

void tim8_init(void){
    //apb1 timer clock set to 200MHz
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_TIM8EN); //enable timer 8
    SET_BIT(TIM8->CR1, TIM_CR1_ARPE); //arr preload enable
    SET_BIT(TIM8->DIER, TIM_DIER_UIE); //update interrupt enable
    WRITE_REG(TIM8->PSC, 0); //set perscaler to 0
    WRITE_REG(TIM8->ARR, 100-1); //overflow at 400
    SET_BIT(TIM8->CR1, TIM_CR1_CEN); //enable counter
    NVIC_EnableIRQ(TIM8_UP_TIM13_IRQn); //enable interrupts for tim14
}

void TIM8_UP_TIM13_IRQHandler(void){
    CLEAR_BIT(TIM8->SR, TIM_SR_UIF);
    dac_update(dds(tuning_word));

}