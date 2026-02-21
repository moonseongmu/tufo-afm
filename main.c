#include<stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "main.h"
#include "dds.h"

uint32_t ticks;
uint16_t v_out;
int dds_updated = 0;

int main(void){
    clock_setup();
    peripheral_init();

    SysTick_Config(100000);
    __enable_irq();
    while(1){
        if(dds_updated == 1){
            printf(">out:%d\r\n", v_out);
            dds_updated = 0;
        }
    }
    
    
}

void tim9_init(void){
    RCC->APB2ENR |= RCC_APB2ENR_TIM9EN;
    asm("nop"); //delay 1+ppre1 cycles as per errata
    asm("nop");
    asm("nop");

    TIM9->PSC = 0; //set prescaler to zero
    TIM9->ARR = 200-1; //set reload value to overlfow at 200, 100MHz/200 = 500kHz
    TIM9->DIER |= TIM_DIER_UIE; //update interrupt enable
    TIM9->CR1 |= TIM_CR1_CEN; //enable counter
    NVIC_EnableIRQ(TIM1_BRK_TIM9_IRQn); //enable timer 9 uodate interrupt
}

void TIM1_BRK_TIM9_IRQHandler(void){
    TIM9->SR &= ~TIM_SR_UIF; //clear update interrupt flag
    v_out= dds(858);
    dds_updated = 1;
}

void clock_setup(void){
    //set flash latency to ws3
    FLASH->ACR |= FLASH_ACR_LATENCY_3WS;
    while((FLASH->ACR & FLASH_ACR_LATENCY_3WS) != 0x3){asm("nop");}
    //power interface clock enable 
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    asm("nop"); //delay 1+ppre1 cycles as per errata
    asm("nop");
    asm("nop");

    //set power voltage scaling 1 mode
    PWR->CR |= PWR_CR_VOS_Msk;

    //set pll config registers to 0
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM_Msk;
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN_Msk;
    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP_Msk;

    //HSE as pll clck src
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE; 

    // set pllm as 12
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLM_2; 
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLM_3; 

    //set plln as 96
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_5; 
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLN_6; 

    //set pllp as 2

    //HSE on
    RCC->CR |= RCC_CR_HSEON;
    while(!(RCC->CR & RCC_CR_HSERDY)){asm("nop");}

    //set AHB prescaler to 1

    //set APB1 prescaler to 2
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;
    for(int i = 0; i < 16; i++){asm("nop");}

    //set APB2 prescaler to 1

    //PLL on
    RCC->CR |= RCC_CR_PLLON;
    while(!(RCC->CR & RCC_CR_PLLRDY)){asm("nop");}

    //select pll as system clock
    RCC->CFGR |= RCC_CFGR_SW_PLL;

    SystemCoreClockUpdate();
}

void peripheral_init(void){

    //enable GPIOA clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN; 
    asm("nop"); //delay for 2 cycles as per errata sheet
    asm("nop");

    //enable syscfg clock
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    asm("nop"); //delay 1+ppre1 cycles as per errata
    asm("nop");
    asm("nop");

    uart_init(115200);
    tim9_init();
}



void delay_ms(uint32_t millisecs){
    uint32_t start = ticks;
    uint32_t end = start + millisecs;

    if (end < start){
        while (ticks > start){asm("nop");} // wait for ticks to wrap around to zero
    }

    while (ticks < end){asm("nop");}
}

void SysTick_Handler(){
    ticks++;
}

