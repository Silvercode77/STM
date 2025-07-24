#include "stm32f407xx.h"
#include "GPIO.h"
#include <stdlib.h>

void InitLed(uint8_t Redun);
void SideWaysLed(uint8_t Redun);
uint8_t i = 0;
void (*Task[2])(uint8_t) = {InitLed, SideWaysLed};

void GPIO_Init(void);

void delay_ms(uint32_t ms);

volatile uint32_t tick_count = 0;

int main(void)
{
    __enable_irq();
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

    Task[i](3);
}

void InitLed(uint8_t Redun)
{
    static uint8_t current = 12;
    static uint32_t Period = 0;
    if (Period == 0)
    {
        Period = SystemCoreClock;
    }
    static uint8_t Freq = 0;
    static uint8_t Recur = 0;

    GPIOD->ODR &= ~(0b1111 << 12);
    GPIOD->ODR |= (1 << current);

    current++;
    if (current == 16)
    {

        Period = Period / 2;
        SysTick->LOAD = (uint32_t)(Period - 1UL);
        SysTick->VAL = 0UL;
        current = 12;
        Freq++;
        if (Freq == 4)
        {
            Period = Period * 2;
            Freq--;
            Recur++;
        }
        if (Recur == Redun){
            Recur=0;
            NextLedPlay();
        }
    }
};

void SideWaysLed(uint8_t Redun)
{
    static uint8_t Dir[2]={0b0011,0b0101};
    static uint8_t dir=0;
    if(dir==0){
        dir=(rand() % 2);
    }
    static uint8_t Recur = 0;
    static uint8_t current = 12;
    if (current == 12)
    {
        GPIOD->ODR &= ~(0XF << 12);
        GPIOD->ODR |= (Dir[dir]<< 12);
        current++;
    }
    else
    {
        GPIOD->ODR &= ~(0XF << 12);
        GPIOD->ODR |= ((0xF-Dir[dir]) << 12);
        current--;
    }
    Recur++;
    if (Recur == Redun)
    {
        Recur = 0;
        dir=0;
        NextLedPlay();
    }
}
void DiagnalLed(uint8_t Recur){

}

void NextLedPlay()
{
    {
        uint8_t fr = (rand() % 5) + 2;
        SysTick->LOAD = (uint32_t)(SystemCoreClock / fr);
        SysTick->VAL = 0UL;
        i = (rand() % 2);
    }
}