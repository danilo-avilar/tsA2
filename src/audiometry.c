/* audiometry.c (v1.0.0)
 * Descrição: Funções para tratamento do teste simplificado de acuidade auditiva
 * 
 * Autor: Danilo Avilar Silva (daniloavilar@gmail.com)
 *
 * Licença: MIT
 * Copyright (c) 2025 Danilo Avilar
 */

#include <stdlib.h>
#include <string.h>
#include "audiometry.h"
#include "oled.h"
#include "handlers.h"
#include "buzzer.h"

volatile uint16_t ADMT_countAcuityFreq = 0;
volatile bool ADMT_nextTest = false;
volatile uint8_t ADMT_test = 1;
volatile bool ADMT_success[sizeof(ADMT_FREQUENCY_RANGE)] = {0};
volatile bool ADMT_heard = 0;

// Mensagem inicial
void ADMT_welcome(){

  OLED_writeString(0, OLED_LINE1, "TESTE SIMPLIFICADO DE ", true);
  OLED_writeString(0, OLED_LINE2, "  ACUIDADE AUDITIVA   ", true);
  OLED_writeString(0, OLED_LINE5, "       ATENCAO        ", true);
  OLED_writeString(0, OLED_LINE6, "    IREMOS INICIAR    ", true);
  OLED_update(HNDL_I2C_PORT); 
  sleep_ms(6000); 
  OLED_clear();
}

// Mensagem final
void ADMT_end(){

  uint8_t success = 0;
  char str[10];

  OLED_clear();

  for(uint8_t i=0; i<sizeof(ADMT_FREQUENCY_RANGE); i++){
    if(ADMT_success[i] == 1){
      success++;
      OLED_writeString((6*i)+(i*6), OLED_LINE4, "v", true);
    } else{
      OLED_writeString((6*i)+(i*6), OLED_LINE5, "x", true);
    }
  }

  if(!ADMT_heard){
    // Ouvido direito
    ADMT_heard = true;
  } else{
    // Ouvido esquerdo
    ADMT_heard = false;
  }  
  OLED_writeString(0, OLED_LINE1, "    > AGUARDE... <    ", true);
  OLED_writeString(0, OLED_LINE2, "FREQUENCIAS (kHz)     ", true);
  
  OLED_writeString(0, OLED_LINE3, "                      ", true);
  for(uint8_t i=0; i<sizeof(ADMT_FREQUENCY_RANGE); i++){
    itoa(ADMT_FREQUENCY_RANGE[i], str, 10);
    OLED_writeString((6*i)+(6*i), OLED_LINE3, str, true);
  }

  OLED_writeString(0, OLED_LINE6, "EXITO:  /  ->       % ", true);
  
  itoa(success, str, 10);
  OLED_writeString(42, OLED_LINE6, str, true);
  
  itoa(sizeof(ADMT_FREQUENCY_RANGE), str, 10);
  OLED_writeString(54, OLED_LINE6, str, true);
  
  HNDL_ftoa((float)(success*100)/sizeof(ADMT_FREQUENCY_RANGE), str, 2);
  OLED_writeString(83, OLED_LINE6, str, true);
  
  OLED_update(HNDL_I2C_PORT); 
  sleep_ms(20000); 
  OLED_clear();
  
  //resetar flags para começar de novo
  ADMT_test = 1;
  memset((bool *)ADMT_success, 0, sizeof(ADMT_success));
}

// Tratamento do teste de acuidade auditiva
void ADMT_hearingAcuity(){
  
  static char str[10];
  
  if(!HNDL_btnCPress && !ADMT_nextTest){
    OLED_writeString(0, OLED_LINE1, "FREQ.  kHz ( / )    s", true);
    
    itoa(ADMT_FREQUENCY_RANGE[ADMT_test-1], str, 10);
    OLED_writeString(36, OLED_LINE1, str, true);
    
    itoa(ADMT_test, str, 10);
    OLED_writeString(72, OLED_LINE1, str, true);
    
    itoa(sizeof(ADMT_FREQUENCY_RANGE), str, 10);
    OLED_writeString(84, OLED_LINE1, str, true);
    
    itoa(ADMT_TIMER_ACUITY_HEARING/1000, str, 10);
    OLED_writeString(108, OLED_LINE1, str, true);
    
    if(!ADMT_heard){OLED_writeString(0, OLED_LINE3, "  OCLUIR OUVIDO DIR.  ", true);}
    else{OLED_writeString(0, OLED_LINE3, "  OCLUIR OUVIDO ESQ.  ", true);}
    OLED_writeString(0, OLED_LINE4, "                     ", true);
    OLED_writeString(0, OLED_LINE5, " PRESSIONE O BOTAO C ", true);
    OLED_writeString(0, OLED_LINE6, "   PARA CONTINUAR    ", true);
    OLED_update(HNDL_I2C_PORT); 
  } else if(ADMT_nextTest){
    itoa(ADMT_FREQUENCY_RANGE[ADMT_test-1], str, 10);
    OLED_writeString(36, OLED_LINE1, str, true);
    
    itoa(ADMT_test, str, 10);
    OLED_writeString(72, OLED_LINE1, str, true);
    
    itoa((int)(ADMT_countAcuityFreq/1000)/10, str, 10);
    OLED_writeString(108, OLED_LINE1, str, true);
    
    itoa((int)(ADMT_countAcuityFreq/1000)%10, str, 10);
    OLED_writeString(114, OLED_LINE1, str, true);
    
    OLED_writeString(0, OLED_LINE3, "> SOM AUDIVEL?       ", true);
    OLED_writeString(0, OLED_LINE4, "    PRESSIONE BOTAO A", true);
    OLED_writeString(0, OLED_LINE5, "> CASO CONTRARIO     ", true);
    OLED_writeString(0, OLED_LINE6, "    PRESSIONE BOTAO B", true);
    OLED_update(HNDL_I2C_PORT);
  }
}
