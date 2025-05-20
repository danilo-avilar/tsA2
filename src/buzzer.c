/* buzzer.c (v1.0.0)
 * Descrição: Funções de controle do buzzer
 * 
 * Autor: Danilo Avilar Silva (daniloavilar@gmail.com)
 * 
 * Licença: MIT
 * Copyright (c) 2025 Danilo Avilar
 */

#include "buzzer.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "audiometry.h"

volatile bool BUZZ_buzzerFlag = false;
volatile bool BUZZ_lastStateBuzzer = false;

// Função para configurar o PWM no buzzer
void BUZZ_start(uint pin, uint freq){
    gpio_set_function(pin, GPIO_FUNC_PWM);        // Configura o pino como saída PWM
    uint slice_num = pwm_gpio_to_slice_num(pin);  // Obtém o slice PWM
    uint wrap = 125000000 / freq;                 // Calcula o valor de wrap
    pwm_set_wrap(slice_num, wrap);                // Define o valor do wrap
    pwm_set_chan_level(slice_num, pwm_gpio_to_channel(pin), wrap / 12); // Define 50% duty cycle
    pwm_set_enabled(slice_num, true);             // Ativa o PWM
}

// Função para desativar o PWM
void BUZZ_stop(uint pin) {
    uint slice_num = pwm_gpio_to_slice_num(pin);  // Obtém o slice PWM
    pwm_set_enabled(slice_num, false);           // Desativa o PWM
    gpio_set_function(pin, GPIO_FUNC_SIO);       // Restaura o pino para saída digital
    gpio_put(pin, false);                        // Garante que o pino fique em nível baixo

}

// Configura o pino do buzzer
void BUZZ_init(){
    gpio_init(BUZZ_BUZZER);
    gpio_set_dir(BUZZ_BUZZER, GPIO_OUT);
    gpio_put(BUZZ_BUZZER, false);
}

// Atualiza o buzzer
void BUZZ_refresh(){
    if(BUZZ_buzzerFlag && !BUZZ_lastStateBuzzer){
        BUZZ_start(BUZZ_BUZZER, ADMT_FREQUENCY_RANGE[ADMT_test-1]*1000);
        BUZZ_lastStateBuzzer = true;
    } else if(!BUZZ_buzzerFlag && BUZZ_lastStateBuzzer){
        BUZZ_stop(BUZZ_BUZZER);
        BUZZ_lastStateBuzzer = false;
    }
}
