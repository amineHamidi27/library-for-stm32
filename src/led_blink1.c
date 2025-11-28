#include<libopencm3/stm32/rcc.h>
#include<libopencm3/stm32/gpio.h>
 
static void gpio_setup(void) {
    rcc_clock_setup_pll(&rcc_hse_configs[RCC_CLOCK_HSE8_72MHZ]);
    rcc_periph_clock_enable(RCC_GPIOC);
    gpio_set_mode(GPIOC, GPIO_MODE_OUTPUT_2_MHZ, GPIO_CNF_OUTPUT_PUSHPULL, GPIO1);
}
int main() {
gpio_setup();
gpio_set(GPIOC, GPIO1);
    while(1) {
        gpio_toggle(GPIOC, GPIO1);
        for (volatile int i = 0; i < 1000000; i++);
    }
    return 0;               
    }
       