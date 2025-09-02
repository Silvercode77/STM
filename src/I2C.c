#include "stm32f4xx.h"
#include "GPIO.h"
#include <stdio.h>
#include "I2C.h"
#define EEPROM 0x50
#define WRITE_BIT 0b0
#define READ_BIT 0b1

void main()
{
  RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
  RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
  // uint8_t x = 8;

  // Set PB6 and PB7 to alternate function (AF4 for I2C1)
  I2CPinConfigure(GPIOB, I2C1, PIN_6, PIN_7);
  GPIO_MODER_CONFIGURATION(GPIOD, GPIO_MODER_OUTPUT, 15);
  GPIOD->ODR |= (1 << 15);

  // GPIOB->AFR[0] |= (4 << GPIO_AFRL_AFSEL6_Pos | 4 << GPIO_AFRL_AFSEL7_Pos);
  I2CModeConfigure(I2C1, 16, 80, 17);

  I2CStart(I2C1);

  I2CAdress(I2C1, 0x50, WRITE_BIT);
  I2CWriteByte(I2C1, 0x00);
  while (!(I2C1->SR1 & I2C_SR1_TXE))
    ;
  I2CWriteByte(I2C1, 0X98);
  I2C1->CR1 |= I2C_CR1_STOP;
  /*I2C1->CR1 |= I2C_CR1_START;
  while (!(I2C1->SR1 & I2C_SR1_SB));

while (!(I2C1->SR1 & I2C_SR1_TXE));
  I2C1->DR = (0x00);

   while (!(I2C1->SR1 & I2C_SR1_TXE));
  I2C1->DR = (0x98);

  // I2C1->DR = (EEPROM << 1) | READ_BIT;

  I2C1->CR1 |= I2C_CR1_STOP;*/
}
