#ifndef RCC_H
#define RCC_H
#include "stm32f4xx.h"

#include <stdio.h>

// #define RCC_SrcClkSet( SrcClk, CFGR, CR, RDY) do {RCC->CR|=(SrcClk);RCC->CFGR|=(CFRG);RCC->CR|=(CR);while(!(RDY & RCC->CR));}while(0);

#define PLLCLKSRC_HSI (uint8_t)0b0
#define PLLCLKSRC_HSE (uint8_t)0b1
extern uint32_t PCLK1;
extern uint32_t PCLK2;
extern uint8_t BusPos[3];

typedef enum
{
    DIV1 = 0b000,
    DIV2 = 0b100,
    DIV4 = 0b101,
    DIV8 = 0b110,
    DIV16 = 0b111,
    DIV32 = 0b1000
} FreqDiv;

typedef enum
{
    RCC_SysCLK_HSI = (uint8_t)0b00,
    RCC_SysCLK_HSE = (uint8_t)0b01,
    RCC_SysCLK_PLL = (uint8_t)0b10,
    Unacceptable = (uint8_t)0b11,
    RCC_SysCLK_PLL_HSI = (0b0 << RCC_PLLCFGR_PLLSRC_Pos),
    RCC_SysCLK_PLL_HSE = (0b1 << RCC_PLLCFGR_PLLSRC_Pos),

} RCC_SysCLK;

typedef enum
{
    RCC_AHB = (uint8_t)0,
    RCC_APB1 = (uint8_t)1,
    RCC_APB2 = (uint8_t)2,

} RCC_BUS;




RCC_SysCLK RCC_SrcCLKGet();

void RCC_UpdatePCLK1();

void RCC_UpdatePCLK2();

void RCC_SetFreq(RCC_BUS Bus, FreqDiv Divider);
void RCCUpdateClocks();

void RCC_SrcClkSet(uint32_t CFGR_clk_on_bit, uint32_t CFGR_clk_ready_bit, uint32_t CR_sw_bits, uint32_t CR_sws_bits);

int8_t RCC_SetPLLfreq(uint8_t PLLCLKSRC, uint8_t PLLQ, uint16_t PLLN, uint8_t PLLM, uint8_t PLLP);

#endif

/*RCCGetCLK(){
RCC->
}*/