#include "stm32f407xx.h"
#include "Systick.h"

// FIRST NON INTERRUPT TIMER SINCE ADDING THE INTERUPT FLAG TO CONTROL CAN MESS THINGS UP FOR THE USUAL TIMER SINCE AFTER EACH ONTERRUPT
// IT WILL ENTER THE IRQ ROUTI,E AND IF YOU DONT HAVE DEFINE IT NOTHING WILL WORK AND BTW THE COUTFALG GETS CLEARED BY READING SO
// while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)); CLEARS THINGS UP AND THE INTERRUPT AUTO CLEARS IT TOO SO ITS ALL GOOD NO NEED FOR MANUAL FLAG CLEAN UP

/*1ST METHOD */ /*Divides 1s by half each time*/
int SystickSec(float PeriodSec)
{
 uint32_t RegisterLoad= (uint32_t)((PeriodSec*SystemCoreClock)-1UL);
   uint8_t result= SysTick_Config(RegisterLoad);
    SysTick->VAL = 0;
    SysTick->CTRL =  SysTick_CTRL_CLKSOURCE_Msk|SysTick_CTRL_ENABLE_Msk; // Systick config enables inteerupt and like we said we dont want that so
    return result;
  

}
CheckSysTimer()
{
  while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk))
    ;
}
//2ND METHOD is used to wait in ms 


void SysTickMs(void)
{
  SysTick->LOAD = (uint32_t)((SystemCoreClock / 1000) - 1UL); // 1ms delay for 16MHz clock
  // SysTick->LOAD = 16000-1;
  SysTick->VAL = 0;
  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;
}

void delay_ms(uint32_t PeriodMs)
{
  for (uint32_t i = 0; i < PeriodMs; i++)
  {
    // Wait for COUNTFLAG
    while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk))
      ;
    // Clear flag by reading it
    volatile uint32_t dummy = SysTick->CTRL;
  }
}
