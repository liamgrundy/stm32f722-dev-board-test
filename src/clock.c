#include "clock.h"
#include <stm32f722xx.h>

void configure_clock(void) {
    RCC->CR |= RCC_CR_HSEON;
    while (!(RCC->CR & RCC_CR_HSERDY)) {
    }

    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR1 |= PWR_CR1_VOS;

    RCC->PLLCFGR = (12 << RCC_PLLCFGR_PLLM_Pos) |
                   (216 << RCC_PLLCFGR_PLLN_Pos) |
                   (0 << RCC_PLLCFGR_PLLP_Pos) |
                   (9 << RCC_PLLCFGR_PLLQ_Pos) |
                   RCC_PLLCFGR_PLLSRC_HSE;

    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY)) {
    }

    FLASH->ACR = FLASH_ACR_LATENCY_7WS |
                 FLASH_ACR_PRFTEN |
                 FLASH_ACR_ARTEN;

    RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;
    RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;

    RCC->CFGR &= ~RCC_CFGR_SW;
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);
}
