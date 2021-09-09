cmake_minimum_required(VERSION 3.11)

project(mfmmod)

include_directories(include)

add_subdirectory(src)

if(DEFINED AVR)
  add_subdirectory(examples)
endif()

enable_testing()
add_subdirectory(tests)