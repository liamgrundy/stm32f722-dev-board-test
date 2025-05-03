#include "clock.h"
#include "gpio.h"
#include <stm32f722xx.h>
#include <FreeRTOS.h>
#include <task.h>

uint8_t ucHeap[ configTOTAL_HEAP_SIZE ] __attribute__((aligned(8), section(".freertos_heap")));

struct LedFlashConfig {
    uint8_t pin_num;
    TickType_t delay_ms;
};

[[noreturn]] void flash_led(void const *pParameters) {
    struct LedFlashConfig const *config = pParameters;
    for(;;) {
        set_pin(config->pin_num, 1);
        vTaskDelay(config->delay_ms / portTICK_PERIOD_MS);
        set_pin(config->pin_num, 0);
        vTaskDelay(config->delay_ms / portTICK_PERIOD_MS);
    }
}

int main(void) {
    configure_clock();

    // Enable clock to GPIOB (bit 1 in AHB1ENR)
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    init_gpio(4);
    init_gpio(5);
    init_gpio(6);
    init_gpio(7);

    struct LedFlashConfig *config1 = pvPortMalloc(sizeof (struct LedFlashConfig));
    config1->pin_num = 4;
    config1->delay_ms = 400;
    xTaskCreate(
            (TaskFunction_t)&flash_led,
            "led_task1",
            1024,
            config1,
            1,
            NULL);

    struct LedFlashConfig *config2 = pvPortMalloc(sizeof (struct LedFlashConfig));
    config2->pin_num = 5;
    config2->delay_ms = 500;
    xTaskCreate(
            (TaskFunction_t)&flash_led,
            "led_task2",
            1024,
            config2,
            1,
            NULL);

    struct LedFlashConfig *config3 = pvPortMalloc(sizeof (struct LedFlashConfig));
    config3->pin_num = 6;
    config3->delay_ms = 600;
    xTaskCreate(
            (TaskFunction_t)&flash_led,
            "led_task4",
            1024,
            config3,
            1,
            NULL);

    struct LedFlashConfig *config4 = pvPortMalloc(sizeof (struct LedFlashConfig));
    config4->pin_num = 7;
    config4->delay_ms = 700;
    xTaskCreate(
            (TaskFunction_t)&flash_led,
            "led_task4",
            1024,
            config4,
            1,
            NULL);

    vTaskStartScheduler();
}

[[noreturn]] void vAssertCalled([[maybe_unused]] const char *pcFile, [[maybe_unused]] unsigned long ulLine) {
    taskDISABLE_INTERRUPTS();
    for (;;) {
    }
}
