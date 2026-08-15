cmake_minimum_required(VERSION 3.22)

project(mcal)
enable_language(C CXX ASM)

# Set target-specific MCU paths and source files
if(MCU STREQUAL "STM32L496")
    set(MCAL_INCLUDES
        st-stm32l4/include
    )
    set(MCAL_SOURCES_ASM
        st-stm32l4/gcc-arm/startup_stm32l496xx.s
    )
    set(MCAL_SOURCES_C
        st-stm32l4/source/gpio.c
        st-stm32l4/source/rcc.c
        st-stm32l4/source/systick.c
        st-stm32l4/source/uart.c
    )
else()
    message(FATAL_ERROR "Unsupported MCU: ${MCU}")
endif()

add_library(mcal INTERFACE)

target_include_directories(mcal INTERFACE
    ${MCAL_INCLUDES}
)

target_sources(mcal INTERFACE
    ${MCAL_SOURCES_ASM}
    ${MCAL_SOURCES_C}
)

target_link_libraries(mcal INTERFACE
    lib
)

# Prepend the include list and source files with the current directory path
list(TRANSFORM MCAL_INCLUDES PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)
list(TRANSFORM MCAL_SOURCES_C PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)

# Export the collected includes and source files to the global lists
set(INCLUDES
    ${INCLUDES}
    ${MCAL_INCLUDES}
    PARENT_SCOPE
)
set(SOURCES_C
    ${SOURCES_C}
    ${MCAL_SOURCES_C}
    PARENT_SCOPE
)
