#include"stm32f407xx.h"
#include"GPIO.h"
#include"Uart.h"
#include "Systick.h"

void main()
   /*
   {
   example implementation*
   
   
   RCC->APB1ENR|= RCC_APB1ENR_UART4EN;
   RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;

UartPinConfiguration(UART4,GPIOA,PIN_0,PIN_1);
UartModeConfiguration(UART4,USART_CR1_TE,0,0);
UART4->BRR=0X8B;
SystickSec(0.5);
char b[]="yobro";

while (1)
{
   UartWrite(UART4,b,sizeof(b));
   CheckSysTimer();
}
}  */



