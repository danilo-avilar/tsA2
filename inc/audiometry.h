#ifndef AUDIOMETRY_H
#define AUDIOMETRY_H

//-------------------------------
// Bibliotecas
#include "handlers.h"
//-------------------------------
// Definições gerais
#define ADMT_TIMER_ACUITY_HEARING 15000
#define ADMT_FREQUENCY_RANGE ((const uint8_t[]){3, 5, 7, 8, 9})
// Variáveis já declaradas
extern volatile uint16_t ADMT_countAcuityFreq;
extern volatile bool ADMT_nextTest;
extern volatile uint8_t ADMT_test;
extern volatile bool ADMT_success[sizeof(ADMT_FREQUENCY_RANGE)];
extern volatile bool ADMT_heard;
//-------------------------------
// Protótipos de funções
void ADMT_welcome();
void ADMT_end();
void ADMT_hearingAcuity();
//-------------------------------

#endif /* AUDIOMETRY_H */