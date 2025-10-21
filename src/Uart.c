#include"stm32f407xx.h"
#include"GPIO.h"
#include"Uart.h"
#include "Systick.h"
#include"RCC.h"

void main()
   
   {
   //example implementation*
   
   
   RCC->APB1ENR|= RCC_APB1ENR_UART4EN;
   RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;

UartPinConfiguration(UART4,GPIOA,PIN_0,PIN_1);
UartModeConfiguration(UART4,USART_CR1_TE|USART_CR1_RE,0,0);

UartBaudrate(UART4,PCLK1,115200,RCC_CR1_OVR16);
SystickSec(0.1);

char b[]="yobro";
char rec[4];
char r;
while (1)
{
   
   while (!(UART4->SR & USART_SR_RXNE));
   r=UART4->DR;
   while (!(UART4->SR&USART_SR_TXE));
   UART4->DR=r;
    while (!(UART4->SR&USART_SR_TC));
   
  
   
   CheckSysTimer();
}
}  



