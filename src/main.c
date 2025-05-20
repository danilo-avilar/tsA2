/* main.c (v1.0.0)
 * Descrição: Rotina principal do firmware
 * 
 * Autor: Danilo Avilar Silva (daniloavilar@gmail.com)
 *
 * Licença: MIT
 * Copyright (c) 2025 Danilo Avilar
 */

#include "handlers.h"
#include "audiometry.h"
#include "buzzer.h"

int main() {
  // Configuração inicial dos periféricos
  HNDL_configInit();

  // Configuração da interrupção de timer para 1ms
  struct repeating_timer timer;
  add_repeating_timer_ms(1, HNDL_timerIrqCallback, NULL, &timer);
  
  // Mensagem inicial
  ADMT_welcome(); 

  while(true){
    if(ADMT_test <= sizeof(ADMT_FREQUENCY_RANGE)){
      ADMT_hearingAcuity();
      BUZZ_refresh();
    } else{
      ADMT_end();
      ADMT_welcome();
    }
  }
}
