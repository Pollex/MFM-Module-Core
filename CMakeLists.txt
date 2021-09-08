cmake_minimum_required(VERSION 3.11)

######################
## AVR Compiler
######################

set(AVR_MCU attiny814)
set(AVR_UPLOADTOOL avrdude)
set(AVR_PROGRAMMER atmelice_updi)
set(AVR_UPLOADTOOL_PORT usb)
include(gcc-avr.cmake)

######################
## Library
######################

set(PROJECT_NAME mfmmod)
project(${PROJECT_NAME})
include_directories(include)

file(GLOB SRC_FILES "src/**/*.c") # Load all files in src folder
add_avr_library(${PROJECT_NAME} ${SRC_FILES})


######################
## Examples
######################

add_subdirectory(examples)