#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include "easy_gpio.h" 

int main(void) {
    rcc_clock_setup_pll(&rcc_hse_configs[RCC_CLOCK_HSE8_72MHZ]);
    easy_gpio_setup(GPIOC, GPIO2| GPIO1, PIN_OUTPUT);

    while (1) {
        gpio_toggle(GPIOC, GPIO2);
        for (int i =0; i<800000;i++)__asm__("nop");
        gpio_toggle(GPIOC, GPIO1);
        for (int i =0; i<800000;i++)__asm__("nop"); // Attente approximative
    }
    return 0;
}