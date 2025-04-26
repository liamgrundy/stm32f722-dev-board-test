#include <stm32f722xx.h>
#include <FreeRTOS.h>
#include <task.h>

extern "C" {
    uint8_t ucHeap[ configTOTAL_HEAP_SIZE ] __attribute__((aligned(8), section(".freertos_heap")));
}

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

struct LedFlashConfig {
    uint8_t pin_num;
    TickType_t delay_ms;
};

void flash_led(void *pParameters) {
    auto *config = reinterpret_cast<LedFlashConfig*>(pParameters);
    for(;;) {
        set_pin(config->pin_num, true);
        vTaskDelay(config->delay_ms / portTICK_PERIOD_MS);
        set_pin(config->pin_num, false);
        vTaskDelay(config->delay_ms / portTICK_PERIOD_MS);
    }
}


int main() {
    // Enable clock to GPIOB (bit 1 in AHB1ENR)
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    init_gpio(4);
    init_gpio(5);
    init_gpio(6);
    init_gpio(7);

    auto *config1 = (LedFlashConfig*)pvPortMalloc(sizeof (LedFlashConfig));
    config1->pin_num = 4;
    config1->delay_ms = 400;
    xTaskCreate(
            &flash_led,
            "led_task1",
            1024,
            config1,
            1,
            nullptr);

    auto *config2 = (LedFlashConfig*)pvPortMalloc(sizeof (LedFlashConfig));
    config2->pin_num = 5;
    config2->delay_ms = 500;
    xTaskCreate(
            &flash_led,
            "led_task2",
            1024,
            config2,
            1,
            nullptr);

    auto *config3 = (LedFlashConfig*)pvPortMalloc(sizeof (LedFlashConfig));
    config3->pin_num = 6;
    config3->delay_ms = 600;
    xTaskCreate(
            &flash_led,
            "led_task4",
            1024,
            config3,
            1,
            nullptr);

    auto *config4 = (LedFlashConfig*)pvPortMalloc(sizeof (LedFlashConfig));
    config4->pin_num = 7;
    config4->delay_ms = 700;
    xTaskCreate(
            &flash_led,
            "led_task4",
            1024,
            config4,
            1,
            nullptr);

    vTaskStartScheduler();
}

extern "C" {
    void vAssertCalled([[maybe_unused]] const char *pcFile, [[maybe_unused]] unsigned long ulLine) {
        taskDISABLE_INTERRUPTS();
        for (;;);
    }
}
