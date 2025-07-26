#include "stm32f407xx.h"

volatile int tx_count = 0;

static void delay(volatile uint32_t count) {
    while (count--);
}

// USART2 interrupt handler
void USART2_IRQHandler(void) {
    if (USART2->SR & USART_SR_TC) {
        // Transmission complete
        GPIOD->ODR ^= (1 << 12);     // Toggle LED on PD12
        delay(1000000);              // Visible delay

        // Send next character
        USART2->DR = 'Z';
        tx_count++;
    }
}

int main(void) {
    // === Enable peripheral clocks ===
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;     // GPIOA for PA2 (TX)
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;     // GPIOD for LED
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;    // USART2 is on APB1

    // === Configure PA2 as USART2_TX (AF7) ===
    GPIOA->MODER &= ~(3 << (2 * 2));             // Clear MODER2
    GPIOA->MODER |=  (2 << (2 * 2));             // Set to Alternate Function
    GPIOA->AFR[0] &= ~(0xF << (4 * 2));           // Clear AFRL2
    GPIOA->AFR[0] |=  (7 << (4 * 2));             // Set AF7 for USART2_TX

    // === Configure PD12 as output (LED) ===
    GPIOD->MODER &= ~(3 << (12 * 2));
    GPIOD->MODER |=  (1 << (12 * 2));

    // === Configure USART2 ===
    USART2->BRR = SystemCoreClock / 115200;       // Assuming 16 MHz system clock
    USART2->CR1 = USART_CR1_TE | USART_CR1_TCIE | USART_CR1_UE;

    // === Enable USART2 interrupt in NVIC ===
    NVIC_EnableIRQ(USART2_IRQn);

    // === Start first transmission ===
    USART2->DR = 'Z';

    while (1) {
        // Main loop does nothing — handled in ISR
    }
}
