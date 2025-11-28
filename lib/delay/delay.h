/* delay.h */
#ifndef DELAY_H
#define DELAY_H

#include <stdint.h>
#define NVIC_TIM2_IRQ 28
void delay_init(void);
void delay_ms(uint32_t ms);
// Ce prototype doit être dans un fichier .h
void nvic_enable_irq(uint8_t irq_number);
#endif