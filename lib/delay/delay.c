/* delay.c - Code de délai basé sur Timer 2 */

#include "delay.h" // Inclut votre header local
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>
#include <libopencm3/cm3/nvic.h> // <--- INCLUSION CRUCIALE AJOUTÉE
#include <libopencm3/cm3/systick.h> // Souvent nécessaire pour des dépendances communes

// Variable globale volatile pour le délai
static volatile uint32_t timer_delay_count = 0;

// Fonction pour initialiser le Timer 2 à 1000 Hz (1 ms)
void tim2_delay_init(void) {
    // 1. Activer l'horloge du périphérique Timer 2
    rcc_periph_clock_enable(RCC_TIM2);

    // 2. Configuration du Timer 2 (pour une interruption toutes les 1 ms)
    // rcc_clock_freq[1] donne la fréquence de l'APB1 (où se trouve le TIM2)
    const uint32_t apb1_freq = rcc_clock_freq[1]; 
    
    // Configurer le prescaler pour que le compteur s'incrémente 1000 fois par seconde (1kHz = 1ms)
    // Prescaler = (Fréquence_APB1 / 1000) - 1
    timer_set_prescaler(TIM2, (apb1_freq / 1000) - 1); 

    // 3. Définir la valeur de rechargement (période)
    timer_set_period(TIM2, 1); // Compte jusqu'à 1 tick (1ms)

    // 4. Activer l'interruption dans le contrôleur d'interruptions (NVIC)
    nvic_enable_irq(NVIC_TIM2_IRQ); // Maintenant connu grâce à nvic.h
    timer_enable_irq(TIM2, TIM_DIER_UIE);

    // 5. Démarrer le compteur
    timer_enable_counter(TIM2);
}

// Handler d'interruption du TIM2 (nom standard dans libopencm3)
void tim2_isr(void) {
    // Vider le flag d'interruption pour pouvoir recommencer à compter
    if (timer_get_flag(TIM2, TIM_SR_UIF)) {
        timer_clear_flag(TIM2, TIM_SR_UIF);
        timer_delay_count++;
    }
}

// Fonction de délai non-bloquante
void delay_ms_tim(uint32_t ms) {
    uint32_t target_count = timer_delay_count + ms;
    
    // Attente (bloquante dans cet exemple simple)
    while (timer_delay_count < target_count);
}

// Pour garantir la visibilité de rcc_clock_freq[] :
extern const uint32_t rcc_clock_freq[];