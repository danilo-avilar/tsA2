#ifndef OLED_H
#define OLED_H

//-------------------------------
// Bibliotecas
#include "hardware/i2c.h"
#include <stdio.h>
//-------------------------------
// Definições do Display OLED SSD1306
#define OLED_I2C_ADDR 0x3C
#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_I2C_CLOCK 400 // Define o tempo do clock (pode ser aumentado)
// Definições de pixel para cada linha do display
#define OLED_LINE1 0
#define OLED_LINE2 11
#define OLED_LINE3 23
#define OLED_LINE4 34
#define OLED_LINE5 45
#define OLED_LINE6 56
//-------------------------------
// Fonte 5x7 (caracteres ASCII de 32 a 126)
static const uint8_t font5x7[][5] = {
    // Definição completa da fonte 5x7
    {0x00,0x00,0x00,0x00,0x00}, // Espaço
    {0x00,0x00,0x5F,0x00,0x00}, // !
    {0x00,0x07,0x00,0x07,0x00}, // "
    {0x14,0x7F,0x14,0x7F,0x14}, // #
    {0x24,0x2A,0x7F,0x2A,0x12}, // $
    {0x23,0x13,0x08,0x64,0x62}, // %
    {0x36,0x49,0x55,0x22,0x50}, // &
    {0x00,0x05,0x03,0x00,0x00}, // '
    {0x00,0x1C,0x22,0x41,0x00}, // (
    {0x00,0x41,0x22,0x1C,0x00}, // )
    {0x14,0x08,0x3E,0x08,0x14}, // *
    {0x08,0x08,0x3E,0x08,0x08}, // +
    {0x00,0x50,0x30,0x00,0x00}, // ,
    {0x08,0x08,0x08,0x08,0x08}, // -
    {0x00,0x60,0x60,0x00,0x00}, // .
    {0x20,0x10,0x08,0x04,0x02}, // /
    {0x3E,0x51,0x49,0x45,0x3E}, // 0
    {0x00,0x42,0x7F,0x40,0x00}, // 1
    {0x72,0x49,0x49,0x49,0x46}, // 2
    {0x21,0x41,0x49,0x4D,0x33}, // 3
    {0x18,0x14,0x12,0x7F,0x10}, // 4
    {0x27,0x45,0x45,0x45,0x39}, // 5
    {0x3C,0x4A,0x49,0x49,0x31}, // 6
    {0x41,0x21,0x11,0x09,0x07}, // 7
    {0x36,0x49,0x49,0x49,0x36}, // 8
    {0x46,0x49,0x49,0x29,0x1E}, // 9
    {0x00,0x36,0x36,0x00,0x00}, // :
    {0x00,0x56,0x36,0x00,0x00}, // ;
    {0x08,0x14,0x22,0x41,0x00}, // <
    {0x14,0x14,0x14,0x14,0x14}, // =
    {0x00,0x41,0x22,0x14,0x08}, // >
    {0x02,0x01,0x59,0x09,0x06}, // ?
    {0x3E,0x41,0x5D,0x59,0x4E}, // @
    {0x7C,0x12,0x11,0x12,0x7C}, // A
    {0x7F,0x49,0x49,0x49,0x36}, // B
    {0x3E,0x41,0x41,0x41,0x22}, // C
    {0x7F,0x41,0x41,0x22,0x1C}, // D
    {0x7F,0x49,0x49,0x49,0x41}, // E
    {0x7F,0x09,0x09,0x09,0x01}, // F
    {0x3E,0x41,0x49,0x49,0x7A}, // G
    {0x7F,0x08,0x08,0x08,0x7F}, // H
    {0x00,0x41,0x7F,0x41,0x00}, // I
    {0x20,0x40,0x41,0x3F,0x01}, // J
    {0x7F,0x08,0x14,0x22,0x41}, // K
    {0x7F,0x40,0x40,0x40,0x40}, // L
    {0x7F,0x02,0x0C,0x02,0x7F}, // M
    {0x7F,0x04,0x08,0x10,0x7F}, // N
    {0x3E,0x41,0x41,0x41,0x3E}, // O
    {0x7F,0x09,0x09,0x09,0x06}, // P
    {0x3E,0x41,0x51,0x21,0x5E}, // Q
    {0x7F,0x09,0x19,0x29,0x46}, // R
    {0x46,0x49,0x49,0x49,0x31}, // S
    {0x01,0x01,0x7F,0x01,0x01}, // T
    {0x3F,0x40,0x40,0x40,0x3F}, // U
    {0x1F,0x20,0x40,0x20,0x1F}, // V
    {0x3F,0x40,0x38,0x40,0x3F}, // W
    {0x63,0x14,0x08,0x14,0x63}, // X
    {0x07,0x08,0x70,0x08,0x07}, // Y
    {0x61,0x51,0x49,0x45,0x43}, // Z
    {0x00,0x7F,0x41,0x41,0x00}, // [
    {0x02,0x04,0x08,0x10,0x20}, // Backslash
    {0x00,0x41,0x41,0x7F,0x00}, // ]
    {0x04,0x02,0x01,0x02,0x04}, // ^
    {0x40,0x40,0x40,0x40,0x40}, // _
    {0x00,0x01,0x02,0x04,0x00}, // `
    {0x20,0x54,0x54,0x54,0x78}, // a
    {0x7F,0x48,0x44,0x44,0x38}, // b
    {0x38,0x44,0x44,0x44,0x20}, // c
    {0x38,0x44,0x44,0x48,0x7F}, // d
    {0x38,0x54,0x54,0x54,0x18}, // e
    {0x08,0x7E,0x09,0x01,0x02}, // f
    {0x0C,0x52,0x52,0x52,0x3E}, // g
    {0x7F,0x08,0x04,0x04,0x78}, // h
    {0x00,0x44,0x7D,0x40,0x00}, // i
    {0x20,0x40,0x44,0x3D,0x00}, // j
    {0x7F,0x10,0x28,0x44,0x00}, // k
    {0x00,0x41,0x7F,0x40,0x00}, // l
    {0x7C,0x04,0x18,0x04,0x78}, // m
    {0x7C,0x08,0x04,0x04,0x78}, // n
    {0x38,0x44,0x44,0x44,0x38}, // o
    {0x7C,0x14,0x14,0x14,0x08}, // p
    {0x08,0x14,0x14,0x18,0x7C}, // q
    {0x7C,0x08,0x04,0x04,0x08}, // r
    {0x48,0x54,0x54,0x54,0x20}, // s
    {0x04,0x3F,0x44,0x40,0x20}, // t
    {0x3C,0x40,0x40,0x20,0x7C}, // u
    {0x1C,0x20,0x40,0x20,0x1C}, // v
    {0x3C,0x40,0x30,0x40,0x3C}, // w
    {0x44,0x28,0x10,0x28,0x44}, // x
    {0x0C,0x50,0x50,0x50,0x3C}, // y
    {0x44,0x64,0x54,0x4C,0x44}, // z
    {0x00,0x08,0x36,0x41,0x00}, // {
    {0x00,0x00,0x7F,0x00,0x00}, // |
    {0x00,0x41,0x36,0x08,0x00}, // }
    {0x08,0x08,0x2A,0x1C,0x08}, // ->
    {0x08,0x1C,0x2A,0x08,0x08}, // <-
    {0x38,0x44,0x45,0x45,0x38}, // à
    {0x38,0x54,0x55,0x55,0x18}, // á
    {0x38,0x44,0x45,0x45,0x20}, // â
    {0x38,0x55,0x54,0x55,0x18}, // ã
    {0x38,0x55,0x55,0x55,0x18}, // é
    {0x38,0x54,0x55,0x55,0x20}, // ê
    {0x38,0x54,0x55,0x55,0x38}, // í
    {0x38,0x44,0x45,0x45,0x38}, // ó
    {0x38,0x55,0x54,0x55,0x38}, // õ
    {0x38,0x55,0x55,0x55,0x38}, // ú
    {0x38,0x54,0x55,0x55,0x20}, // ü
    {0x38,0x44,0x7E,0x44,0x38}, // ç
    {0x7C,0x12,0x11,0x12,0x7C}, // Á  
    {0x7C,0x12,0x11,0x12,0x7C}, // À  
    {0x7C,0x12,0x11,0x12,0x7C}, // Ã  
    {0x7C,0x12,0x11,0x12,0x7C}, // Â  
    {0x7C,0x12,0x11,0x12,0x7C}, // Ä 
    {0x38,0x54,0x54,0x54,0x18}, // É  
    {0x38,0x54,0x54,0x54,0x18}, // Ê
    {0x3E,0x48,0x48,0x48,0x30}, // Í  
    {0x3E,0x48,0x48,0x48,0x30}, // Ì  
    {0x3E,0x48,0x48,0x48,0x30}, // Î  
    {0x3E,0x48,0x48,0x48,0x30}, // Ï  
    {0x3E,0x41,0x41,0x41,0x3E}, // Ó  
    {0x3E,0x41,0x41,0x41,0x3E}, // Ò  
    {0x3E,0x41,0x41,0x41,0x3E}, // Õ  
    {0x3E,0x41,0x41,0x41,0x3E}, // Ô  
    {0x3E,0x41,0x41,0x41,0x3E}, // Ö  
    {0x3E,0x41,0x41,0x41,0x3E}, // Ø  
    {0x7E,0x41,0x41,0x22,0x1C}, // Ú  
    {0x7E,0x41,0x41,0x22,0x1C}, // Ù  
    {0x7E,0x41,0x41,0x22,0x1C}, // Û  
    {0x7E,0x41,0x41,0x22,0x1C}, // Ü  
    {0x7E,0x09,0x09,0x09,0x06}, // Ç  
    {0x30,0x48,0x45,0x40,0x20} // Ñ
};
//-------------------------------
// Protótipos de funções
void OLED_init(i2c_inst_t *i2c);
void OLED_clear();
void OLED_update(i2c_inst_t *i2c);
void OLED_drawPixel(int x, int y, bool color);
void OLED_drawChar(int x, int y, char c, bool color);
void OLED_writeString(int x, int y, const char *str, bool color);
//-------------------------------

#endif // OLED_H
