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

void set_pin(uint8_t pin, bool value) {
    GPIOB->ODR &= ~(1 << pin);
    GPIOB->ODR |= ((value != 0) << pin);
}

void delay() {
    for (uint32_t i = 0; i != 2000000; ++i) {
        asm volatile ("nop");
    }
}

int main() {
    // Enable clock to GPIOB (bit 1 in AHB1ENR)
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    init_gpio(4);
    init_gpio(5);
    init_gpio(6);
    init_gpio(7);

    while (1) {
        for (uint8_t i = 4; i <= 7; ++i) {
            delay();
            set_pin(i, true);
        }
        for (uint8_t i = 7; i >= 4; --i) {
            delay();
            set_pin(i, false);
        }
    }
}
