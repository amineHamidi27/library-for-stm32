/* easy_gpio.h */
#ifndef EASY_GPIO_H
#define EASY_GPIO_H

#include <stdint.h>
// On a besoin de libopencm3 pour que le compilateur comprenne uint32_t etc.
#include <libopencm3/stm32/gpio.h> 

// Définition de ton type personnalisé
typedef enum {
    PIN_OUTPUT,
    PIN_INPUT,
    PIN_INPUT_PULLUP
} PinMode;

// Prototype de ta fonction (la promesse qu'elle existe)
void easy_gpio_setup(uint32_t port, uint16_t pin, PinMode mode);

#endif