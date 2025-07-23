#include "stm32f407xx.h"
#include "GPIO.h"

void GPIO_Init(void);
void delay_ms(uint32_t ms);

volatile uint32_t tick_count = 0;

int main(void)
{

    GPIO_Init();
    SysTick_Config(SystemCoreClock);

    while (1)
    {
    }
}

void GPIO_Init(void)
{

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

    GPIO_MODER_CONFIGURATION(GPIOD, GPIO_MODER_OUTPUT, Pin12 | Pin13 | Pin14 | Pin15);
}
void delay_ms(uint32_t ms)
{
    tick_count = 0;
    while (tick_count < ms)
        ;
}

// SysTick Handler
void SysTick_Handler(void)
{
    static uint8_t current = 12;
    static uint32_t Period = 0;
     if(Period==0){
        Period=SystemCoreClock;
    }
    static uint8_t Recur=0;
   
    GPIOD->ODR&=~(0b1111<<12);
    GPIOD->ODR|=(1<<current);
    
    current++;
    if (current == 16)
    {
       
        Period = Period / 2;
        SysTick->LOAD=(uint32_t)(Period - 1UL); ;
        SysTick->VAL=0UL;
        current = 12;
        Recur++;
        if(Recur==4){
        Period=Period*2;
        Recur--;
    }
    }
  

}
