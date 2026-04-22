#include "main.h"
#include "gpio.h"
#include "dds.h"
#include "dac.h"


uint32_t ticks;

int main(void){
    clock_config();
    peripherals_init();
    __enable_irq();
    tuning_word = freq_to_tuning_word(32768, 2000000);
    while (1)
    {
        gpio_toggle_pin(GPIOE, GPIO_Pin_3);
        delay_ms(500);
    }
}

void clock_config(void){
    MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY,FLASH_ACR_LATENCY_2WS);
    MODIFY_REG(FLASH->ACR, FLASH_ACR_WRHIGHFREQ,FLASH_ACR_WRHIGHFREQ_1); //set flash wait states and flash signal delay
    while(READ_BIT(FLASH->ACR, FLASH_ACR_LATENCY) != FLASH_ACR_LATENCY_2WS){asm("nop");}//wait until flash latency updates
    while(READ_BIT(FLASH->ACR, FLASH_ACR_WRHIGHFREQ) != FLASH_ACR_WRHIGHFREQ_1){asm("nop");} //wait until flash singal delay updates
    
    SET_BIT(PWR->CR3, PWR_CR3_LDOEN); //ldo enable
    while(READ_BIT(PWR->CSR1, PWR_CSR1_ACTVOSRDY) != PWR_CSR1_ACTVOSRDY){ asm("nop");} //wait for vos to rise
    MODIFY_REG(PWR->D3CR, PWR_D3CR_VOS, (PWR_D3CR_VOS_0|PWR_D3CR_VOS_1)); //set vos to 1
    while(READ_BIT(PWR->D3CR, PWR_D3CR_VOSRDY) != PWR_D3CR_VOSRDY){ asm("nop");} //wait for vos to rise

    SET_BIT(RCC->CR, RCC_CR_HSEON);
    while(READ_BIT(RCC->CR, RCC_CR_HSERDY) != RCC_CR_HSERDY){ asm("nop");} //wait until hse stable
    SET_BIT(RCC->PLLCKSELR, RCC_PLLCKSELR_PLLSRC_HSE); //hse as pll src
    SET_BIT(RCC->PLLCFGR, RCC_PLLCFGR_PLL1RGE_2); //set input clock freq of pll1 to 4-8MHz(5MHz)
    MODIFY_REG(RCC->PLLCKSELR, RCC_PLLCKSELR_DIVM1, 2 << RCC_PLLCKSELR_DIVM1_Pos); // divm1 = 2
    MODIFY_REG(RCC->PLL1DIVR, RCC_PLL1DIVR_N1, (64-1) << RCC_PLL1DIVR_N1_Pos); //set pll1 divn1 to 64
    SET_BIT(RCC->CR, RCC_CR_PLL1ON);
    while(READ_BIT(RCC->CR, RCC_CR_PLL1RDY) != RCC_CR_PLL1RDY){ asm("nop");} //wait until pll locked
    MODIFY_REG(RCC->D1CFGR, RCC_D1CFGR_HPRE, RCC_D1CFGR_HPRE_DIV2); //set hpre to div by 2
    MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_PLL1); //use pll as system clock, sysclk shld be 400MHz now
    while(READ_BIT(RCC->CFGR, RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL1){asm("nop");}

    MODIFY_REG(RCC->D1CFGR, RCC_D1CFGR_D1PPRE, RCC_D1CFGR_D1PPRE_DIV2); //divide apb clocks by 2
    MODIFY_REG(RCC->D2CFGR, RCC_D2CFGR_D2PPRE1,RCC_D2CFGR_D2PPRE1_DIV2);
    MODIFY_REG(RCC->D2CFGR, RCC_D2CFGR_D2PPRE2,RCC_D2CFGR_D2PPRE2_DIV2);
    MODIFY_REG(RCC->D3CFGR, RCC_D3CFGR_D3PPRE, RCC_D3CFGR_D3PPRE_DIV2);
    
    SystemCoreClockUpdate();

    //systick setup
    
    SysTick_Config(400000);
}

void gpio_init(void){
    SET_BIT(RCC->AHB4ENR, RCC_AHB4ENR_GPIOEEN); //enable gpioe
    MODIFY_REG(GPIOE->MODER, GPIO_MODER_MODER3,GPIO_MODER_MODER3_0); //set e3 to gp output
}


void tim14_init(void){
    //apb1 timer clock set to 200MHz
    SET_BIT(RCC->APB1LENR, RCC_APB1LENR_TIM14EN); //enable timer 14
    SET_BIT(TIM14->CR1, TIM_CR1_ARPE); //arr preload enable
    SET_BIT(TIM14->DIER, TIM_DIER_UIE); //update interrupt enable
    WRITE_REG(TIM14->PSC, 0); //set perscaler to 0
    WRITE_REG(TIM14->ARR, 100-1); //overflow at 400
    SET_BIT(TIM14->CR1, TIM_CR1_CEN); //enable counter
    NVIC_EnableIRQ(TIM8_TRG_COM_TIM14_IRQn); //enable interrupts for tim14
}

void TIM8_TRG_COM_TIM14_IRQHandler(void){
    CLEAR_BIT(TIM14->SR, TIM_SR_UIF);
    dac_update(dds(tuning_word));

}

void peripherals_init(void){
    gpio_init();
    tim14_init();
    dac_init();
}

void delay_ms(uint32_t millisecs){
    uint32_t start = ticks;
    uint32_t end = start + millisecs;

    if (end < start){
        while (ticks > start){asm("nop");} // wait for ticks to wrap around to zero
    }

    while (ticks < end){asm("nop");}
}

void SysTick_Handler(void){
    ticks++;
}

