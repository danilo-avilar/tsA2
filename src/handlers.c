/* handlers.c (v1.0.0)
 * Descrição: Funções de manipulações das interrupções, configurações e de uso geral
 * 
 * Autor: Danilo Avilar Silva (daniloavilar@gmail.com)
 *
 * Licença: MIT
 * Copyright (c) 2025 Danilo Avilar
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "handlers.h"
#include "oled.h"
#include "buzzer.h"
#include "audiometry.h"

volatile int HNDL_debounceBtnA, HNDL_debounceBtnB, HNDL_debounceBtnC;
volatile bool HNDL_btnCPress = false;

// Configurações iniciais
void HNDL_configInit(){
  
  // Configuração da serial para depuração via printf
  stdio_init_all();

  // Configuração da intergace I2C
  // 400kHz, define os pinos e configura resistor pull-up interno
  i2c_init(HNDL_I2C_PORT, OLED_I2C_CLOCK * 1000);
  gpio_set_function(HNDL_SDA, GPIO_FUNC_I2C);
  gpio_set_function(HNDL_SCL, GPIO_FUNC_I2C);
  gpio_pull_up(HNDL_SDA);
  gpio_pull_up(HNDL_SCL);

  // Configuração do buzzer
  BUZZ_init();

  // Configuração dos botões
  gpio_init(HNDL_BTN_A);
  gpio_set_dir(HNDL_BTN_A, GPIO_IN);
  gpio_pull_up(HNDL_BTN_A); // Habilita o resistor pull-up interno para evitar leituras incorretas.
  gpio_init(HNDL_BTN_B);
  gpio_set_dir(HNDL_BTN_B, GPIO_IN);
  gpio_pull_up(HNDL_BTN_B); // Habilita o resistor pull-up interno para evitar leituras incorretas.
  gpio_init(HNDL_BTN_C);
  gpio_set_dir(HNDL_BTN_C, GPIO_IN);
  gpio_pull_up(HNDL_BTN_C); // Habilita o resistor pull-up interno para evitar leituras incorretas.

  // Configuração do display OLED
  OLED_init(HNDL_I2C_PORT);
  OLED_clear();

  // Configuração das interrupções de acionamento dos botões por borda de descida
  gpio_set_irq_enabled_with_callback(HNDL_BTN_A, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true, &HNDL_gpioIrqCallback);
  gpio_set_irq_enabled_with_callback(HNDL_BTN_B, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true, &HNDL_gpioIrqCallback);
  gpio_set_irq_enabled_with_callback(HNDL_BTN_C, GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE, true, &HNDL_gpioIrqCallback);
}

// Função de tratamento de interrupção dos botões
void HNDL_gpioIrqCallback(uint gpio, uint32_t events)
{
    if (gpio == HNDL_BTN_A && !HNDL_debounceBtnA && (events & GPIO_IRQ_EDGE_FALL)){
      //Botão A pressionado
      HNDL_debounceBtnA = 50;
      ADMT_countAcuityFreq = 0;
      ADMT_success[ADMT_test-1] = 1;
    } else if(gpio == HNDL_BTN_A && !HNDL_debounceBtnA && (events & GPIO_IRQ_EDGE_RISE)){
      //Botão A solto
      HNDL_debounceBtnA = 50;
    }

    if (gpio == HNDL_BTN_B && !HNDL_debounceBtnB && (events & GPIO_IRQ_EDGE_FALL)){
      //Botão B pressionado
      HNDL_debounceBtnB = 50;
      ADMT_countAcuityFreq = 0;
      ADMT_success[ADMT_test-1] = 0;
    } else if(gpio == HNDL_BTN_B && !HNDL_debounceBtnB && (events & GPIO_IRQ_EDGE_RISE)){
      //Botão B solto
      HNDL_debounceBtnB = 50;
    }

    if (gpio == HNDL_BTN_C && !HNDL_debounceBtnC && (events & GPIO_IRQ_EDGE_FALL)){
      //Botão C pressionado
      HNDL_debounceBtnC = 50;
      HNDL_btnCPress = true;
      ADMT_countAcuityFreq = ADMT_TIMER_ACUITY_HEARING;
      ADMT_nextTest = true;
      BUZZ_buzzerFlag = true;
    } else if(gpio == HNDL_BTN_C && !HNDL_debounceBtnC && (events & GPIO_IRQ_EDGE_RISE)){
      //Botão C solto
      HNDL_debounceBtnC = 50;
    }
}

// Tratamento da interrupção de timer
bool HNDL_timerIrqCallback(struct repeating_timer *t) {
  
  if(HNDL_debounceBtnA){HNDL_debounceBtnA--;}
  if(HNDL_debounceBtnB){HNDL_debounceBtnB--;}
  if(HNDL_debounceBtnC){HNDL_debounceBtnC--;}

  if(ADMT_countAcuityFreq){ADMT_countAcuityFreq--;}
  else if(ADMT_nextTest){
    ADMT_nextTest = false; 
    HNDL_btnCPress = false;
    ADMT_test++;
    BUZZ_buzzerFlag = false;
  }

  return true;
}

// Converte um float para string
void HNDL_ftoa(float valor, char *str, int casas) {
    snprintf(str, 10, "%.*f", casas, valor);
}
