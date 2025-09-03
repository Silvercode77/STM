#include"stm32f407xx.h"
#include"GPIO.h"


UartWrite(USART_TypeDef * UART, void* buf,size_t size){

   /* for(int i=0;i<size;i++){
        UART4->DR=buf[i];
        while(!(UART4->SR & USART_SR_TC));
    }*/
}