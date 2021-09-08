cmake_minimum_required(VERSION 3.11)

######################
## AVR Compiler
######################

set(MCU attiny814) # ATtiny814

find_program(AVR_CC avr-gcc REQUIRED)
find_program(AVR_CXX avr-g++ REQUIRED)
find_program(AVR_OBJCOPY avr-objcopy REQUIRED)
find_program(AVR_SIZE_TOOL avr-size REQUIRED)
find_program(AVR_OBJDUMP avr-objdump REQUIRED)

# set(CMAKE_VERBOSE_MAKEFILE 1)
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)
set(CMAKE_CROSSCOMPILING 1)
set(CMAKE_C_COMPILER ${AVR_CC})
set(CMAKE_CXX_COMPILER ${AVR_CXX})

set(CMAKE_EXE_LINKER_FLAGS -mmcu=${MCU})
add_compile_options(
    -mmcu=${MCU} # MCU
    -std=gnu99 # C99 standard
    -Os # optimize
    -Wall # enable warnings
    -Wno-main
    -Wundef
    -pedantic
    -Wstrict-prototypes
    -Werror
    -Wfatal-errors
    -Wl,--relax,--gc-sections
    -g
    -gdwarf-2
    -funsigned-char # a few optimizations
    -funsigned-bitfields
    -fpack-struct
    -fshort-enums
    -ffunction-sections
    -fdata-sections
    -fno-split-wide-types
    -fno-tree-scev-cprop
)

######################
## Library
######################

set(PROJECT_NAME mfmmod)

project(${PROJECT_NAME})

file(GLOB SRC_FILES "src/*.c") # Load all files in src folder

add_library(${PROJECT_NAME} ${SRC_FILES})
include_directories(include)

######################
## Examples
######################

add_subdirectory(examples)