#ifndef BUZZER_H
#define BUZZER_H

//-------------------------------
// Bibliotecas
#include <pico/types.h>
//-------------------------------
// Definições gerais
#define BUZZ_BUZZER 10
// Variáveis já declaradas
extern volatile bool BUZZ_buzzerFlag;
extern volatile bool BUZZ_lastStateBuzzer;
//-------------------------------
// Protótipos de funções
void BUZZ_start(uint, uint);
void BUZZ_stop(uint);
void BUZZ_init();
void BUZZ_refresh();
//-------------------------------

#endif /* BUZZER_H */