#include"stm32f407xx.h"
#include"GPIO.h"
#include"Uart.h"
#include "Systick.h"

void main(){
RCC->APB1ENR|=RCC_APB1ENR_UART4EN ;
RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;
RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;

GPIOD->MODER|=(GPIO_MODER_OUTPUT<<15*2);
GPIOA->MODER|=((0b10<<0*2)|(0b10<<1*2));
GPIOA->AFR[0]|=((8<<(0*4))|(8<<(1*4)));


UART4->CR1=(0);
UART4->CR2 = 0;  

UART4->CR1|=USART_CR1_UE;
UART4->CR1|=USART_CR1_TE;
UART4->CR2|=(USART_CR2_STOP);
UART4->BRR=(0x8B);


int Period=SystemCoreClock/64;
 
SystickNoInt(1);
while (1)
{
 
GPIOD->ODR^=(1<<15);
    char b[]="yobro";
   for(int i=0;i<sizeof(b);i++){
        UART4->DR=b[i];
        while(!(UART4->SR & USART_SR_TC));
    }

/*UART4->DR='a';
while(!(UART4->SR & USART_SR_TC));
UART4->DR='b';
while(!(UART4->SR & USART_SR_TC));
UART4->DR='c';
while(!(UART4->SR & USART_SR_TC));
UART4->DR='d';
while(!(UART4->SR & USART_SR_TC));
UART4->DR='f';
while(!(UART4->SR & USART_SR_TC));
UART4->DR='g';
while(!(UART4->SR & USART_SR_TC));*/


CheckSysTimer();

}
}

     