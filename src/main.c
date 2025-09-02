#include "stm32f407xx.h"
#include "GPIO.h"
/*int main()
{

    RCC->AHB1RSTR |= RCC_AHB1RSTR_GPIODRST;
    RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_GPIODRST);
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    
    GPIOD->MODER &= ~((3 << 9 * 2) | (3 << (12 * 2)));

    GPIOD->MODER |= ((GPIO_MODER_INPUT << (9 * 2)) | (GPIO_MODER_OUTPUT << (12 * 2)));
    GPIOD->MODER|=((GPIO_MODER_OUTPUT<<(15*2)));

    GPIOD->PUPDR &= ~(3 << (9 * 2));
    GPIOD->PUPDR |= (GPIO_PULLUP << (9 * 2));
    SYSCFG->EXTICR[2] &= ~(0xF << 4); 
    SYSCFG->EXTICR[2] |= (0x3 << 4); 

    EXTI->IMR |= (EXTI_IMR_MR9);
    EXTI->RTSR &= ~(EXTI_RTSR_TR9);
    EXTI->FTSR |= (EXTI_FTSR_TR9);
    
    NVIC_EnableIRQ(EXTI9_5_IRQn);
    NVIC_SetPriority(EXTI9_5_IRQn, 1);

    while (1)
    {
      GPIOD->ODR|=(1<<(15));
}
}
void EXTI9_5_IRQHandler()
{
    if (EXTI->PR & (1 << 9)) {
        GPIOD->ODR ^= (1 << 12);
        EXTI->PR = (1 << 9);           
    }
}*/