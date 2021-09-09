cmake_minimum_required(VERSION 3.11)

project(mfmmod)

include_directories(include)

add_subdirectory(src)
add_subdirectory(tests)

if(DEFINED AVR)
  add_subdirectory(examples)
endif(DEFINED AVR)