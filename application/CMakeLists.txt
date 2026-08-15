cmake_minimum_required(VERSION 3.22)

project(application)
enable_language(C ASM)

# Set application include paths
set(APPLICATION_INCLUDES
    include
)

# Set application source files
set(APPLICATION_SOURCES
    source/button.c
    source/error_handler.c
    source/led.c
    source/log.c
    source/main.c
    source/stm32l4xx_it.c
    source/system_clock.c
    source/system_stm32l4xx.c
)

add_library(application INTERFACE)

target_include_directories(application INTERFACE
    ${APPLICATION_INCLUDES}
)

target_sources(application INTERFACE
    ${APPLICATION_SOURCES}
)

target_link_libraries(application INTERFACE
    lib
    mcal
)

# Prepend the include list and source files with the current directory path
list(TRANSFORM APPLICATION_INCLUDES PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)
list(TRANSFORM APPLICATION_SOURCES PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/)

# Export the collected includes and source files to the global lists
set(INCLUDES
    ${INCLUDES}
    ${APPLICATION_INCLUDES}
    PARENT_SCOPE
)
set(SOURCES_C
    ${SOURCES_C}
    ${APPLICATION_SOURCES}
    PARENT_SCOPE
)
