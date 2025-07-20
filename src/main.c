#include "stm32f407xx.h"
#include "GPIO.h"
int main()
{

    RCC->CR |= RCC_CR_HSION_Msk;
    while (!(RCC->CR & RCC_CR_HSIRDY_Msk))
        ;

    RCC->CFGR |= RCC_CFGR_SW_HSI;
    RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

    SysTick->CTRL |= (SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_CLKSOURCE_Msk);
    SysTick->LOAD |= (800000 - 1);

    RCC->AHB1RSTR |= RCC_AHB1RSTR_GPIODRST;
    RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_GPIODRST);

    RCC->AHB1RSTR |= RCC_AHB1RSTR_GPIOARST;
    RCC->AHB1RSTR &= ~(RCC_AHB1RSTR_GPIOARST);

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

    GPIOD->MODER &= ~((3 << 9 * 2) | (3 << (12 * 2) | (3 << 0)));
    GPIOD->MODER |= ((GPIO_MODER_INPUT << (9 * 2)) | (GPIO_MODER_OUTPUT << (12 * 2)));

    /*GPIOD->PUPDR &= ~(3 << (9 * 2));
    GPIOD->PUPDR |= (GPIO_PULLUP << (9 * 2));*/
    GENERAL_CFGRBIT(GPIOD->PUPDR, GPIO_PULLUP, 9 * 2, 2);

    GPIO_MODER_CONFIGURATION(GPIOA, GPIO_MODER_INPUT, 0);
    GPIO_PUPDR_CONFIGURATION(GPIOA, GPIO_PULLDOWN, 0);

    SYSCFG->EXTICR[2] &= ~(0xF << 4);
    SYSCFG->EXTICR[2] |= (0x3 << 4);

    SYSCFG->EXTICR[0] &= ~(0xF << 0);

    EXTI->IMR |= (EXTI_IMR_MR9);
    EXTI->RTSR &= ~(EXTI_RTSR_TR9);
    EXTI->FTSR |= (EXTI_FTSR_TR9);

    SYSCFG->EXTICR[0] &= ~(0xF << 0); // EXTI0 connected to PA0

    EXTI->IMR |= (1 << 0);   // Unmask EXTI0
    EXTI->RTSR &= ~(1 << 0); // Disable rising edge
    EXTI->FTSR |= (1 << 0);  // Enable falling edge (button press)

    NVIC_SetPriority(EXTI0_IRQn, 1); // Priority
    NVIC_EnableIRQ(EXTI0_IRQn);      // Enable interrupt

    while (1)
    {
    }
}

void EXTI9_5_IRQHandler()
{
    if (EXTI->PR & (1 << 9))
    {
        GPIOD->ODR ^= (1 << 12);
        EXTI->PR = (1 << 9);
        while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk))
            ;
    }
}

void EXTI0_IRQHandler()
{
    if (EXTI->PR & (1 << 0))
    {
        GPIOD->ODR ^= (1 << 12);
        while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
        EXTI->PR = (1 << 0);
    }
}