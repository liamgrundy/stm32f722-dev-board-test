#include "gpio.h"
#include <stm32f722xx.h>

void init_gpio(uint8_t pin) {
    // Set PB4 as general purpose output (mode 01)
    GPIOB->MODER &= ~(0x3 << (pin * 2));     // Clear mode bits
    GPIOB->MODER |=  (0x1 << (pin * 2));     // Set mode to 01 (output)

    // Set output type to push-pull (default)
    GPIOB->OTYPER &= ~(1 << pin);

    // Set output speed to medium
    GPIOB->OSPEEDR &= ~(0x3 << (pin * 2));
    GPIOB->OSPEEDR |=  (0x1 << (pin * 2));   // Medium speed

    // No pull-up/pull-down
    GPIOB->PUPDR &= ~(0x3 << (pin * 2));
}

void set_pin(uint8_t pin, int value) {
    GPIOB->ODR &= ~(1 << pin);
    GPIOB->ODR |= ((value != 0) << pin);
}
