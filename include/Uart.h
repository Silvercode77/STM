#ifndef UART_H
#define UART_H
#include"stm32f407xx.h"
#include"GPIO.h"
#include"RCC.h"

#define RCC_CR1_OVR8 0b1
#define RCC_CR1_OVR16 0b0

//DONT FORGET TO RCC ENABLE PLS

UartPinConfiguration(USART_TypeDef * USART,GPIO_TypeDef *GPIO,PIN_NUMBER Pin_Tx,PIN_NUMBER Pin_Rx){ //Be carefull We need the pin nmber not position here

    uint8_t AF = ((USART==(USART1))||(USART==(USART2))||(USART==(USART3))) ? 7: 8; //Checks if USART is 1/2/3 the AF is 7 if not then its 4/5/6 then the AF IS 8
    GPIO->MODER|=((0b10<<Pin_Tx*2)|(0b10<<Pin_Rx*2)); 
    ((Pin_Tx < 8)&&(Pin_Rx < 8)) ? (GPIO->AFR[0] |= (AF << (Pin_Tx * 4)) | (AF << (Pin_Rx * 4))):(GPIO->AFR[1] |= (AF << (Pin_Tx * 4)) | (AF << (Pin_Rx * 4)));

}


UartModeConfiguration(USART_TypeDef * USART,uint8_t CR1_FLAGS,uint8_t CR2_FLAGS,uint8_t CR3_FLAGS){
CLEAR_REG(USART->CR1);
CLEAR_REG(USART->CR2);
CLEAR_REG(USART->CR3);
USART->CR1|=(USART_CR1_UE|CR1_FLAGS);
USART->CR2|=(CR2_FLAGS);
USART->CR3|=(CR3_FLAGS);


}

void UartBaudrate(USART_TypeDef *USART, uint32_t PCLK, uint32_t Baudrate,uint8_t OVRSAMPLE)
{
   GENERAL_CFGRBIT(USART->CR1,OVRSAMPLE,USART_CR1_OVER8_Pos,1);
   uint8_t OVR8 = (USART->CR1 & USART_CR1_OVER8_Msk) >> USART_CR1_OVER8_Pos;
    uint32_t USARTDIV;
    uint32_t mantissa;
    uint32_t fraction;

    if (OVR8 == 0) // 16x oversampling
    {
        USARTDIV = (PCLK/ Baudrate)+0.5; // because they are int a/b egts truced auto to the lowest int the fraction part is discarded so 
        mantissa = USARTDIV / 16;        //we add 0.5 if its 8.4 +0.5 its 8.9 it gets truced so its stil 8 but if its > 8.5 it becomes 9 
        fraction = USARTDIV % 16;
        USART->BRR = (mantissa << 4) | fraction;
    }
    else // 8x oversampling
    {
        USARTDIV = (PCLK + (Baudrate/2)) / Baudrate; // another method of rounding 
        mantissa = USARTDIV / 8;
        fraction = USARTDIV % 8;
        USART->BRR = (mantissa << 3) | fraction;
    }
}


void UartWrite(USART_TypeDef * UART, void* buf,size_t size){

    
uint8_t * buffer=(uint8_t*)buf;
    for(int i=0;i<size;i++){
        UART->DR=buffer[i];
        while(!(UART4->SR & USART_SR_TC));
    }
}

/*void UartRead(){

}*/

typedef enum {

    USART_BAUDRATE_9600=4,
    USART_BAUDRATE_115200 =(0X8B),






}USART_BAUDRATE;



#endif