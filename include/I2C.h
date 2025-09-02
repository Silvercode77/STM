#ifndef I2CG_H
#define I2CG_H
#include "stm32f4xx.h"
#include "GPIO.h"
#include <stdio.h>

void I2CPinConfigure(GPIO_TypeDef *GPIO, I2C_TypeDef* I2C, PIN_NUMBER SCL_Pin, PIN_NUMBER SDA_Pin)
{
    GPIO->MODER &= ~((0b11 << (SCL_Pin * 2)) | (0b11 << (SDA_Pin * 2))); // Clear bits
    GPIO->MODER |= (0b10 << (SCL_Pin * 2)) | (0b10 << (SDA_Pin * 2));    // AF mode

    ((SCL_Pin < 8)&&(SDA_Pin < 8)) ? (GPIO->AFR[0] |= (4 << (SCL_Pin * 4)) | (4 << (SDA_Pin * 4))):(GPIO->AFR[1] |= (4 << (SCL_Pin * 4)) | (4 << (SDA_Pin * 4)));

    GPIO->OTYPER |= (1 << SCL_Pin) | (1 << SDA_Pin);               // Open-drain
    GPIO->OSPEEDR |= (GPIO_OSPEEDR_HIGH << (SCL_Pin * 2)) | (GPIO_OSPEEDR_VERYHIGH << (SDA_Pin * 2));  // High speed
    GPIO->PUPDR |= (GPIO_PULLUP << (SCL_Pin * 2)) | (GPIO_PULLUP << (SDA_Pin * 2));    // Pull-up
}

void I2CModeConfigure(I2C_TypeDef *I2C, uint32_t APB1CLK, uint32_t SCL_Freq, uint32_t Trise)
{
    I2C->CR1 &= ~I2C_CR1_PE;

    I2C->CR2 = APB1CLK;  // PCLK1 = 16 MHz
    I2C->CCR = SCL_Freq; // 100kHz standard mode
    I2C->TRISE = Trise;  // TRISE = (1000ns / T_PCLK) + 1 = 17

    I2C->CR1 |= I2C_CR1_PE; // Enable I2C
};

void I2CStart(I2C_TypeDef *I2C){

     I2C->CR1 |= I2C_CR1_START;
   
     while (!(I2C->SR1 & I2C_SR1_SB)) ;  // if the SB so start contion is 0 redo if 1 continue

}
void I2CAdress(I2C_TypeDef * I2C,uint32_t Addr,uint8_t RW_Mode){

    I2C->DR = (Addr << 1) | RW_Mode; // while (!(I2C1->SR1 & I2C_SR1_TXE));

    while (!(I2C->SR1 & I2C_SR1_ADDR));  // if the addrr is 0 REDO if its 1 continue
    
    // clear ADDR
    (void)(I2C->SR1); 
    (void)(I2C->SR2); 
}

void I2CWriteByte(I2C_TypeDef * I2C,uint32_t Byte){

 while (!(I2C->SR1 & I2C_SR1_TXE));
 I2C->DR = (Byte);

}
#endif