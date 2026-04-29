#include "dma.h"
#include "stm32h7xx.h"
#include "main.h"

void dma_init(void){
    SET_BIT(RCC->AHB1ENR, RCC_AHB1ENR_DMA1EN); //enable dma1
    CLEAR_BIT(DMA1_Stream0->CR, DMA_SxCR_EN); //disable dma stream
    while(READ_BIT(DMA1_Stream0->CR, DMA_SxCR_EN)){asm("nop");} //wait for dma stream to disable
    WRITE_REG(DMA1_Stream0->PAR, (uint32_t) &(DAC1->DHR8R1)); //dac 8 bit output register
    WRITE_REG(DMA1_Stream0->M0AR, (uint32_t)&dac_out_buffer_1); //dac output buffer 1
    WRITE_REG(DMA1_Stream0->M1AR, (uint32_t)&dac_out_buffer_2); //dac output buffer 2
    WRITE_REG(DMA1_Stream0->NDTR, BLOCK_SIZE); //set number of itens to block size;
    MODIFY_REG(DMAMUX1_Channel0->CCR, DMAMUX_CxCR_DMAREQ_ID, 67 << DMAMUX_CxCR_DMAREQ_ID_Pos); //set dac ch1 as req input
    MODIFY_REG(DMA1_Stream0->CR, DMA_SxCR_PL, DMA_SxCR_PL); //set dma priority to very high
    CLEAR_BIT(DMA1_Stream0->FCR, DMA_SxFCR_DMDIS); //direct mode enable
    MODIFY_REG(DMA1_Stream0->CR, DMA_SxCR_DIR, DMA_SxCR_DIR_1); //memory to periph
    SET_BIT(DMA1_Stream0->CR, DMA_SxCR_MINC); //mem increment mode
    CLEAR_BIT(DMA1_Stream0->CR, DMA_SxCR_PINC); //no periph increment
    SET_BIT(DMA1_Stream0->CR, DMA_SxCR_DBM); //double buffer mode
    CLEAR_BIT(DMA1_Stream0->CR, DMA_SxCR_MSIZE); //set byte size for both mmory and peripheral
    CLEAR_BIT(DMA1_Stream0->CR, DMA_SxCR_PSIZE);
    SET_BIT(DMA1_Stream0->CR, DMA_SxCR_TCIE); //transfer complete interrupt enable
    SET_BIT(DMA1_Stream0->CR, DMA_SxCR_EN); //enable dma
    NVIC_EnableIRQ(DMA1_Stream0_IRQn); //enable stream 0 irq
}

