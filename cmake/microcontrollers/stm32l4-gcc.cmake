# Set linker script
set(LINKER_SCRIPT
    ${PROJECT_SOURCE_DIR}/mcal/st-stm32l4/gcc-arm/stm32l496xx_flash.ld
)
if(NOT EXISTS ${LINKER_SCRIPT})
    message(FATAL_ERROR "Linker script \"${LINKER_SCRIPT}\" does not exist!")
endif()

# Set debug flags (Debug build type)
set(DEBUG_FLAGS
    "-Og"
    "-g"
)

# Set release flags (Release build type)
set(RELEASE_FLAGS
    "-O3"
    "-DNDEBUG"
)

# Set flags for release with optimization for minimum size
# (MinSizeRel build type)
set(MINSIZEREL_FLAGS
    "-Os"
    "-DNDEBUG"
)

# Set flags for release with debug info but no debug (output) code or asserts
# (RelWithDebInfo build type)
set(RELWITHDEBINFO_FLAGS
    "-O2"
    "-g"
    "-DNDEBUG"
)

# Set microcontroller-specific compiler flags
set(MCU_FLAGS
    "-mcpu=cortex-m4"
    "-mthumb"
    "-mfpu=fpv4-sp-d16"
    "-mfloat-abi=hard"
)

# Set assembler flags
set(ASM_FLAGS
    "-x assembler-with-cpp"
)

# Set C compiler flags
set(C_FLAGS
    "-MMD"
    "-MP"
)

# Set CXX compiler flags
set(CXX_FLAGS
    "-fno-rtti"
    "-fno-exceptions"
    "-fno-threadsafe-statics"
)

# Set common compiler flags
set(COMMON_FLAGS
    "-Wall"
    "-Werror"
    "-Wextra"
    "-pedantic"
    "-fdata-sections"
    "-ffunction-sections"
)

# Set linker flags
set(LINKER_FLAGS
    "-T${LINKER_SCRIPT}"
    "-specs=nano.specs"
    "-specs=nosys.specs"
    "-Wl,-Map=${CMAKE_PROJECT_NAME}.map,--cref"
    "-Wl,--gc-sections"
    "-Wl,--start-group -lc -lm -lnosys -Wl,--end-group"
    "-Wl,--print-memory-usage"
)

# Enable link time optimization for MinSizeRel builds
if(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    list(APPEND C_FLAGS
        "-flto"
    )
    list(APPEND LINKER_FLAGS
        "-flto"
    )
endif()

# For all build types:
# Join the build type flags (separated by space character) into one string
# Set the created string containing the build type flags for all languages
list(JOIN DEBUG_FLAGS " " DEBUG_FLAGS)
set(CMAKE_ASM_FLAGS_DEBUG ${DEBUG_FLAGS})
set(CMAKE_C_FLAGS_DEBUG ${DEBUG_FLAGS})
set(CMAKE_CXX_FLAGS_DEBUG ${DEBUG_FLAGS})

list(JOIN RELEASE_FLAGS " " RELEASE_FLAGS)
set(CMAKE_ASM_FLAGS_RELEASE ${RELEASE_FLAGS})
set(CMAKE_C_FLAGS_RELEASE ${RELEASE_FLAGS})
set(CMAKE_CXX_FLAGS_RELEASE ${RELEASE_FLAGS})

list(JOIN MINSIZEREL_FLAGS " " MINSIZEREL_FLAGS)
set(CMAKE_ASM_FLAGS_MINSIZEREL ${MINSIZEREL_FLAGS})
set(CMAKE_C_FLAGS_MINSIZEREL ${MINSIZEREL_FLAGS})
set(CMAKE_CXX_FLAGS_MINSIZEREL ${MINSIZEREL_FLAGS})

list(JOIN RELWITHDEBINFO_FLAGS " " RELWITHDEBINFO_FLAGS)
set(CMAKE_ASM_FLAGS_RELWITHDEBINFO ${RELWITHDEBINFO_FLAGS})
set(CMAKE_C_FLAGS_RELWITHDEBINFO ${RELWITHDEBINFO_FLAGS})
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO ${RELWITHDEBINFO_FLAGS})

# For all languages:
# Specify the compiler flags and join all flags into one string
set(CMAKE_ASM_FLAGS ${ASM_FLAGS} ${MCU_FLAGS} ${C_FLAGS} ${COMMON_FLAGS})
list(JOIN CMAKE_ASM_FLAGS " " CMAKE_ASM_FLAGS)

set(CMAKE_C_FLAGS   ${MCU_FLAGS} ${C_FLAGS} ${COMMON_FLAGS})
list(JOIN CMAKE_C_FLAGS " " CMAKE_C_FLAGS)

set(CMAKE_CXX_FLAGS ${MCU_FLAGS} ${C_FLAGS} ${CXX_FLAGS} ${COMMON_FLAGS})
list(JOIN CMAKE_CXX_FLAGS " " CMAKE_CXX_FLAGS)

# Specify the linker flags and join all flags into one string
set(CMAKE_EXE_LINKER_FLAGS  ${MCU_FLAGS} ${LINKER_FLAGS})
list(JOIN CMAKE_EXE_LINKER_FLAGS " " CMAKE_EXE_LINKER_FLAGS)
