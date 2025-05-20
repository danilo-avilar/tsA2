/* oled.c (v1.0.0)
 * Descrição: Funções de controle do display OLED ssd1302
 * 
 * Autor: Aleksander Alekseev (gitHub: @afiskon)
 * Data de Criação: 2018
 * Ultima Modificação: 06/02/2025
 * 
 * Licença: MIT
 * Copyright (c) 2025 Danilo Avilar
 * 
 * Histórico de Modificações:
 * - 06/02/2025: Adaptação das funções de interesse baseada na biblioteca stm32-ssd1306 (https://github.com/afiskon/stm32-ssd1306) (Danilo Avilar)
 */

#include "oled.h"
#include "handlers.h"
#include <string.h>

// Buffer para armazenar os pixels do display
static uint8_t buffer[OLED_WIDTH * OLED_HEIGHT / 8];

// Funções auxiliares para enviar comandos e dados
static void OLED_writeCommand(i2c_inst_t *i2c, uint8_t cmd) {
    uint8_t data[2] = {0x00, cmd};
    i2c_write_blocking(i2c, OLED_I2C_ADDR, data, 2, false);
}

// Escrita de comando
static void OLED_writeData(i2c_inst_t *i2c, uint8_t *data, size_t len) {
    uint8_t buf[len + 1];
    buf[0] = 0x40; // Co = 0, D/C# = 1
    memcpy(buf + 1, data, len);
    i2c_write_blocking(i2c, OLED_I2C_ADDR, buf, len + 1, false);
}

// Inicialização do display
void OLED_init(i2c_inst_t *i2c) {
    sleep_ms(100); // Tempo para o display iniciar

    // Sequência de inicialização do SSD1306
    OLED_writeCommand(i2c, 0xAE); // Display OFF
    OLED_writeCommand(i2c, 0x20); // Set Memory Addressing Mode
    OLED_writeCommand(i2c, 0x00); // Horizontal Addressing Mode
    OLED_writeCommand(i2c, 0xB0); // Set Page Start Address for Page Addressing Mode
    OLED_writeCommand(i2c, 0xC8); // COM Output Scan Direction remapped mode
    OLED_writeCommand(i2c, 0x00); // Set low column address
    OLED_writeCommand(i2c, 0x10); // Set high column address
    OLED_writeCommand(i2c, 0x40); // Set start line address
    OLED_writeCommand(i2c, 0x81); // Set contrast control
    OLED_writeCommand(i2c, 0xFF);
    OLED_writeCommand(i2c, 0xA1); // Set segment re-map 0 to 127
    OLED_writeCommand(i2c, 0xA6); // Set normal display
    OLED_writeCommand(i2c, 0xA8); // Set multiplex ratio(1 to 64)
    OLED_writeCommand(i2c, 0x3F); // 1/64 duty
    OLED_writeCommand(i2c, 0xA4); // Output follows RAM content
    OLED_writeCommand(i2c, 0xD3); // Set display offset
    OLED_writeCommand(i2c, 0x00); // No offset
    OLED_writeCommand(i2c, 0xD5); // Set display clock divide ratio/oscillator frequency
    OLED_writeCommand(i2c, 0xF0); // Set divide ratio
    OLED_writeCommand(i2c, 0xD9); // Set pre-charge period
    OLED_writeCommand(i2c, 0x22);
    OLED_writeCommand(i2c, 0xDA); // Set com pins hardware configuration
    OLED_writeCommand(i2c, 0x12);
    OLED_writeCommand(i2c, 0xDB); // Set vcomh
    OLED_writeCommand(i2c, 0x20);
    OLED_writeCommand(i2c, 0x8D); // Set DC-DC enable
    OLED_writeCommand(i2c, 0x14);
    OLED_writeCommand(i2c, 0xAF); // Turn on SSD1306 panel
}

// Limpeza do display
void OLED_clear() {
    memset(buffer, 0, sizeof(buffer));
    OLED_update(HNDL_I2C_PORT);
}

// Exibe as informações no display
void OLED_update(i2c_inst_t *i2c) {
    for (uint8_t page = 0; page < 8; page++) {
        OLED_writeCommand(i2c, 0xB0 + page);
        OLED_writeCommand(i2c, 0x00);
        OLED_writeCommand(i2c, 0x10);
        OLED_writeData(i2c, &buffer[OLED_WIDTH * page], OLED_WIDTH);
    }
}

// Manipulação de pixel
void OLED_drawPixel(int x, int y, bool color) {
    if (x < 0 || x >= OLED_WIDTH || y < 0 || y >= OLED_HEIGHT)
        return;

    if (color)
        buffer[x + (y / 8) * OLED_WIDTH] |= (1 << (y % 8));
    else
        buffer[x + (y / 8) * OLED_WIDTH] &= ~(1 << (y % 8));
}

// Escreve um caractere
void OLED_drawChar(int x, int y, char c, bool color) {
    if (c < 32 || c > 126)
        return;

    for (int i = 0; i < 5; i++) {
        uint8_t line = font5x7[c - 32][i];
        for (int j = 0; j < 8; j++) {
            OLED_drawPixel(x + i, y + j, (line & 0x01) ? color : !color);
            line >>= 1;
        }
    }
}

// Escreve uma string
void OLED_writeString(int x, int y, const char *str, bool color) {
    while (*str) {
        OLED_drawChar(x, y, *str++, color);
        x += 6; // Avançar 6 pixels (5 de largura + 1 de espaço)
    }
}
