cmake_minimum_required(VERSION 3.22)

project(stm32-project-template)
enable_language(C CXX ASM)

# Set the following variable to `ON` to print all cmake variables
set(CMAKE_DUMP_VARIABLES            OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS   ON)

set(CMAKE_C_STANDARD                11)
set(CMAKE_C_STANDARD_REQUIRED       ON)
set(CMAKE_C_EXTENSIONS              ON)
set(CMAKE_CXX_STANDARD              14)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            ON)

# Define the default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()
message(NOTICE "Build type: ${CMAKE_BUILD_TYPE}")

# Include the required build tools
include(cmake/tools/clang-tools.cmake)
include(cmake/tools/python.cmake)

# Include the microcontroller-specific parameters
include(cmake/microcontrollers/stm32l4-gcc.cmake)

# Add library files
add_subdirectory(lib)

# Set defines
set(DEFINES
    STM32L496xx
    USE_HAL_DRIVER
    USE_FULL_ASSERT
    $<$<CONFIG:Debug>:DEBUG>
)

# Set include paths
set(INCLUDES
    ${PROJECT_SOURCE_DIR}/mcal/st-stm32l4/include
    ${PROJECT_SOURCE_DIR}/include
)

# Set source files
set(SOURCES_ASM
    ${PROJECT_SOURCE_DIR}/mcal/st-stm32l4/gcc-arm/startup_stm32l496xx.s
)
set(SOURCES_C
    ${PROJECT_SOURCE_DIR}/mcal/st-stm32l4/source/gpio.c
    ${PROJECT_SOURCE_DIR}/mcal/st-stm32l4/source/rcc.c
    ${PROJECT_SOURCE_DIR}/mcal/st-stm32l4/source/systick.c
    ${PROJECT_SOURCE_DIR}/mcal/st-stm32l4/source/uart.c
    ${PROJECT_SOURCE_DIR}/source/button.c
    ${PROJECT_SOURCE_DIR}/source/error_handler.c
    ${PROJECT_SOURCE_DIR}/source/led.c
    ${PROJECT_SOURCE_DIR}/source/log.c
    ${PROJECT_SOURCE_DIR}/source/main.c
    ${PROJECT_SOURCE_DIR}/source/stm32l4xx_it.c
    ${PROJECT_SOURCE_DIR}/source/system_clock.c
    ${PROJECT_SOURCE_DIR}/source/system_stm32l4xx.c
)

# Specify target executable
add_executable(${CMAKE_PROJECT_NAME})

# Specify target compile definitions
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    ${DEFINES}
)

# Specify target include directories
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${INCLUDES}
)

# Specify target source files
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    ${SOURCES_ASM}
    ${SOURCES_C}
)

# Specify libraries to link
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    lib
)

# Generate size information
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${CMAKE_PROJECT_NAME}>
)

# Generate binary output
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.bin
    COMMAND ${CMAKE_COMMAND} -E echo "Create bin output: ${TARGET_BIN_OUTPUT}"
)

# Generate hex output
add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${CMAKE_PROJECT_NAME}> ${CMAKE_PROJECT_NAME}.hex
    COMMAND ${CMAKE_COMMAND} -E echo "Create hex output: ${TARGET_HEX_OUTPUT}"
)

# Add custom target to check source code formatting with clang-format
add_custom_target(check-format
    COMMAND ${Python_EXECUTABLE} ${PROJECT_SOURCE_DIR}/script/clang_format.py
            --check
            --style=file
            --executable=${CLANG_FORMAT}
            ${INCLUDES} ${SOURCES_C}
    COMMENT "Check source code formatting..."
)

# Add custom target to run clang-format
add_custom_target(run-format
    COMMAND ${Python_EXECUTABLE} ${PROJECT_SOURCE_DIR}/script/clang_format.py
            --style=file
            --executable=${CLANG_FORMAT}
            ${INCLUDES} ${SOURCES_C}
    COMMENT "Run source code formatting..."
)

# Add custom target to generate doxygen documentation
add_custom_target(doxygen
    COMMAND doxygen docs/doxygen/Doxyfile
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMENT "Generate doxygen documentation..."
)

# Add custom target to run clang-tidy
set(CLANG_TIDY_DEFINES
    ${DEFINES}
)
set(CLANG_TIDY_INCLUDES
    ${INCLUDES}
)
list(TRANSFORM CLANG_TIDY_DEFINES PREPEND -D)
list(TRANSFORM CLANG_TIDY_INCLUDES PREPEND -I)
list(TRANSFORM CLANG_TIDY_SYSTEM_INCLUDES PREPEND -isystem)
add_custom_target(tidy
    COMMAND ${CLANG_TIDY}
            ${CLANG_TIDY_ARGS}
            ${SOURCES_C}
            --
            ${CLANG_TIDY_EXTRA_ARGS}
            ${CLANG_TIDY_DEFINES}
            ${CLANG_TIDY_INCLUDES}
            ${CLANG_TIDY_SYSTEM_INCLUDES}
    COMMENT "Run clang-tidy..."
)

# Specify additional clean files
set_property(TARGET ${CMAKE_PROJECT_NAME} APPEND PROPERTY ADDITIONAL_CLEAN_FILES
    ${CMAKE_PROJECT_NAME}.map
    ${CMAKE_PROJECT_NAME}.bin
    ${CMAKE_PROJECT_NAME}.hex
)

# Dump all cmake variables
if(CMAKE_DUMP_VARIABLES)
    get_cmake_property(_variableNames VARIABLES)
    list (SORT _variableNames)
    foreach (_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach()
endif()
