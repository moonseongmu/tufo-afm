#include <stdint.h>
#include "dac.h"
#include "stm32h7xx.h"

void dac_init(void){
    SET_BIT(RCC->APB1LENR, RCC_APB1LENR_DAC12EN); //enable dac
    MODIFY_REG(GPIOA->MODER, GPIO_MODER_MODER4, (GPIO_MODER_MODER4_0|GPIO_MODER_MODER4_1)); //set a4 to alternate mode dac1 out1

    MODIFY_REG(DAC1->MCR, DAC_MCR_MODE1, 0 << DAC_MCR_MODE1_Pos); //set chnl1 as normal mode external pin with buffer
    SET_BIT(DAC1->CR, DAC_CR_EN1); //enable dac channel 1
}

void dac_update(uint8_t val){
    WRITE_REG(DAC1->DHR8R1, val);
}