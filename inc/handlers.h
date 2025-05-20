#ifndef HANDLERS_H
#define HANDLERS_H

//-------------------------------
// Bibliotecas
#include "hardware/i2c.h"
//-------------------------------
// Definições da interface I2C
#define HNDL_I2C_PORT i2c1 // Interface 1
#define HNDL_SDA 14    //  GP14 -> SDA
#define HNDL_SCL 15    //  GP15 -> SCL
// Definições dos botões
#define HNDL_BTN_A 5   // GP5 -> botão A
#define HNDL_BTN_B 6   // GP6 -> botão B
#define HNDL_BTN_C 22  // GP22 -> botão C
// Variáveis já declaradas
extern volatile bool HNDL_btnCPress;
//-------------------------------
// Protótipos de funções
void HNDL_configInit();
void HNDL_gpioIrqCallback(uint, uint32_t);
bool HNDL_timerIrqCallback(struct repeating_timer *);
void HNDL_ftoa(float, char *, int);
//-------------------------------

#endif /* HANDLERS_H */