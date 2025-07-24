#include "stm32f407xx.h"
#include "GPIO.h"
#include <stdlib.h>

void main(){
    RESET(GPIO_A);
    RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN_Msk;
    
}