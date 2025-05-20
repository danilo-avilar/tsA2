# tsA2
Teste Simplificado de Acuidade Auditiva



## Ferramentas
  * VSCode com extensão "CMake Tools"
  * Linguagem: C
  * Toolchain: arm-none-eabi-gcc 13.2.rel1
  * Sistema: Linux (testado no openSUSE 15.4)



## SDK e Bibliotecas
  * Raspberry Pi Pico W SDK v1.5.1
  * stdio, stdlib, string
  * Drivers adicionais:
    * SSD1306 (OLED via I2C)



## Dependências via CMake
  * `pico_stdlib`
  * `hardware_i2c`
  * `hardware_pwm`
  * `hardware_timer`



## Estrutura do Projeto
```
tsA2
    ├── build
    ├── CMakeLists.txt
    ├── inc
    │   ├── audiometry.h
    │   ├── buzzer.h
    │   ├── handlers.h
    │   └── oled.h
    ├── pico_sdk_import.cmake
    ├── README.md
    └── src
        ├── audiometry.c
        ├── buzzer.c
        ├── handlers.c
        ├── main.c
        └── oled.c
```



## Descritivo Geral dos Módulos
### Sources
Arquivos de implementação  
**`audiometry.c`** - Lógica para realização do teste simplificado de acuidade auditiva  
**`buzzer.c`** - Controle do buzzer  
**`handlers.c`** - Funções de manipulação geral  
**`oled.c`** - Controle do display OLED  
**`main.c`** - Loop principal  
### Headers
Definição de protótipos das funções, definições específicas de cada módulo e definições de pinos associados  
**`audiometry.h`**  
> `ADMT_TIMER_ACUITY_HEARING`: Constante que determina o tempo (em ms) de realização de cada etapa do teste de acuidade
> `ADMT_FREQUENCY_RANGE`: Faixas de frequências (em kHz) que serão avaliadas

**`buzzer.h`**  
**`handlers.h`**  
**`oled.h`**  
