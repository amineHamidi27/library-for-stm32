#include "easy_gpio.h"
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

static void enable_port_clock(uint32_t port) {
    switch (port) {
        case GPIOA: rcc_periph_clock_enable(RCC_GPIOA); break;
        case GPIOB: rcc_periph_clock_enable(RCC_GPIOB); break;
        case GPIOC: rcc_periph_clock_enable(RCC_GPIOC); break;
    }
}

void easy_gpio_setup(uint32_t port, uint16_t pin, PinMode mode) {
    enable_port_clock(port); 

    switch (mode) {
        case PIN_OUTPUT:
            gpio_set_mode(port, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, pin);
            break;
        case PIN_INPUT:
            gpio_set_mode(port, GPIO_MODE_INPUT, GPIO_CNF_INPUT_FLOAT, pin);
            break;
        case PIN_INPUT_PULLUP:
            gpio_set_mode(port, GPIO_MODE_INPUT, GPIO_CNF_INPUT_PULL_UPDOWN, pin);
            gpio_set(port, pin);
            break;
    }
}