#include"stm32f407xx.h"
#include"GPIO.h"
#include"Uart.h"
#include"RCC.h"
#include "Systick.h"

/* void main(){
    RCC_SetPLLfreq(PLLCLKSRC_HSI, 8, 128, 16, 8);
    RCC_SrcClkSet(RCC_CR_PLLON, RCC_CR_PLLRDY, RCC_CFGR_SW_PLL, RCC_CFGR_SWS_PLL);
    RCC_SysCLK  st = RCC_SrcCLKGet();
    RCCUpdateClocks();
     //RCC_SetFreq(RCC_AHB, DIV32);
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    GPIOD->MODER |= GPIO_MODER_OUTPUT << 15 * 2;
    SystemCoreClockUpdate();

   SystickSec(0.5);

    while (1)
    {
        GPIOD->ODR ^= (1 << 15);
        CheckSysTimer();
    }



}*/