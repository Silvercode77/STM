
#include "stm32f4xx.h"
#include "GPIO.h"
#include <stdio.h>
#include "RCC.h"

uint32_t PCLK1 = 16000000;
uint32_t PCLK2 = 16000000;
uint8_t BusPos[3] = {RCC_CFGR_HPRE_Pos, RCC_CFGR_PPRE1_Pos, RCC_CFGR_PPRE2_Pos};

void RCC_UpdatePCLK1()
{
    uint8_t tmp;
    tmp = APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE1) >> RCC_CFGR_PPRE1_Pos];
    PCLK1 = SystemCoreClock >> tmp;
}

void RCC_UpdatePCLK2()
{
    uint8_t tmp;
    tmp = APBPrescTable[(RCC->CFGR & RCC_CFGR_PPRE2) >> RCC_CFGR_PPRE2_Pos];
    PCLK2 = SystemCoreClock >> tmp;
}

void RCCUpdateClocks()
{
    SystemCoreClockUpdate();
    RCC_UpdatePCLK1();
    RCC_UpdatePCLK2();
}

void RCC_SrcClkSet(uint32_t CFGR_clk_on_bit, uint32_t CFGR_clk_ready_bit, uint32_t CR_sw_bits, uint32_t CR_sws_bits)
{
    // 1. Enable the oscillator
    RCC->CR |= CFGR_clk_on_bit;

    // 2. Wait until it is ready
    while (!(RCC->CR & CFGR_clk_ready_bit))
        ;

    // 3. Select it as system clock
    RCC->CFGR = (RCC->CFGR & ~RCC_CFGR_SW) | CR_sw_bits;

    // 4. Wait until it is actually used
    while ((RCC->CFGR & RCC_CFGR_SWS) != CR_sws_bits)
        ;
        __NOP();
}

void RCC_SetFreq(RCC_BUS Bus, FreqDiv Divider)
{
    RCC->CFGR |= (Divider << BusPos[Bus]);
    RCCUpdateClocks();
}

RCC_SysCLK RCC_SrcCLKGet()
{
    switch ((RCC->CFGR & RCC_CFGR_SWS) >> RCC_CFGR_SWS_Pos)
    {
    case RCC_SysCLK_HSI:
        return RCC_SysCLK_HSI;
        break;
    case RCC_SysCLK_HSE:
        return RCC_SysCLK_HSE;
        break;

    case RCC_SysCLK_PLL:
        if ((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) >> RCC_PLLCFGR_PLLSRC_Pos)
            return RCC_SysCLK_PLL_HSE;

        else
            return RCC_SysCLK_PLL_HSI;

        break;

    default:
        return Unacceptable;
        break;
    }


}
int8_t RCC_SetPLLfreq(uint8_t PLLCLKSRC, uint8_t PLLQ, uint16_t PLLN, uint8_t PLLM, uint8_t PLLP)
{
    // Validity checks
    if (((PLLQ < 2) || (PLLQ > 15)) ||
        ((PLLN < 50) || (PLLN > 432)) ||
        ((PLLM < 2) || (PLLM > 63)) ||
        ((PLLP != 2) && (PLLP != 4) && (PLLP != 6) && (PLLP != 8)))
    {
        return -1; // invalid input
    }

    // Clear old config but keep reserved bits
    RCC->PLLCFGR = 0;

    // Encode PLLP: register field = (PLLP/2 - 1)
    uint32_t pllP_bits = ((PLLP / 2) - 1) << RCC_PLLCFGR_PLLP_Pos;

    // Build new config
    RCC->PLLCFGR = (PLLCLKSRC << RCC_PLLCFGR_PLLSRC_Pos) |
                   (PLLQ << RCC_PLLCFGR_PLLQ_Pos) |
                   (PLLN << RCC_PLLCFGR_PLLN_Pos) |
                   (PLLM << RCC_PLLCFGR_PLLM_Pos) |
                   pllP_bits;

    return 0;
}
