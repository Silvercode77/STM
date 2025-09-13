#include"stm32f407xx.h"
#include"GPIO.h"




UartPinConfiguration(USART_TypeDef * USART,GPIO_TypeDef *GPIO,PIN_NUMBER Pin_Tx,PIN_NUMBER Pin_Rx){ //Be carefull We need the pin nmber not position here

    uint8_t AF = ((USART==(USART1))||(USART==(USART2))||(USART==(USART3))) ? 7: 8; //Checks if USART is 1/2/3 the AF is 7 if not then its 4/5/6 then the AF IS 8
    GPIO->MODER|=((0b10<<Pin_Tx*2)|(0b10<<Pin_Rx*2)); 
    ((Pin_Tx < 8)&&(Pin_Rx < 8)) ? (GPIO->AFR[0] |= (AF << (Pin_Tx * 4)) | (AF << (Pin_Rx * 4))):(GPIO->AFR[1] |= (AF << (Pin_Tx * 4)) | (AF << (Pin_Rx * 4)));

}


UartModeConfiguration(USART_TypeDef * USART,uint8_t CR1_FLAGS,uint8_t CR2_FLAGS,uint8_t CR3_FLAGS){
CLEAR_REG(USART->CR1);
CLEAR_REG(USART->CR2);
USART->CR1|=(USART_CR1_UE|CR1_FLAGS);
USART->CR2|=(CR2_FLAGS);
USART->CR3|=(CR3_FLAGS);


}

UartBaudarate(USART_TypeDef * USART,uint32_t Baudrate,uint32_t APBCLK){ //Formula UART->BRR=APBCLK/((8*(2-OVR8))*Baudrate)
uint8_t OVR8=(USART->CR1&USART_CR1_OVER8_Msk)>>USART_CR1_OVER8_Pos;
float ResultPart=(APBCLK/((16*Baudrate)));
uint32_t Intpart=(uint32_t) (ResultPart);
uint16_t floatpart= (ResultPart-Intpart)*16;
USART->BRR=(Intpart<<4)|floatpart;
}

UartWrite(USART_TypeDef * UART, void* buf,size_t size){

    
uint8_t * buffer=(uint8_t*)buf;
    for(int i=0;i<size;i++){
        UART->DR=buffer[i];
        while(!(UART4->SR & USART_SR_TC));
    }
}

typedef enum {

    USART_BAUDRATE_9600=4,
    USART_BAUDRATE_115200 =(0X8B),






}USART_BAUDRATE;