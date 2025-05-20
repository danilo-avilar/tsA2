# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 1.5.1)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(tsA2 C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# TODO: Minhas definições
# Defina os diretórios das fontes e cabeçalhos
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INC_DIR ${CMAKE_SOURCE_DIR}/inc)

# Adicione automaticamente todos os arquivos .c do diretório src
file(GLOB SRC_FILES ${SRC_DIR}/*.c)

# Inclua o diretório dos headers
include_directories(${INC_DIR})

# Crie o executável a partir das fontes
add_executable(${CMAKE_PROJECT_NAME} ${SRC_FILES})

# Linke as bibliotecas padrão do Pico
target_link_libraries(${CMAKE_PROJECT_NAME} 
    pico_stdlib 
    hardware_i2c
    hardware_pwm
    hardware_timer
    )

if (PICO_CYW43_SUPPORTED)
   target_link_libraries(${CMAKE_PROJECT_NAME} pico_cyw43_arch_none)
endif()

# Ative a UART e USB (opcional, dependendo do seu projeto)
pico_enable_stdio_usb(${CMAKE_PROJECT_NAME} 1)
pico_enable_stdio_uart(${CMAKE_PROJECT_NAME} 0)

# Copie o executável final para o formato UF2
pico_add_extra_outputs(${CMAKE_PROJECT_NAME})
